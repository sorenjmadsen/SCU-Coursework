// Soren Madsen
// Lab 6
// 18 May 2019
// This program is a Stop and Wait for an Unreliable Channel w/ Loss UDP server that writes to a file.

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include "lab6.h"

/*********************
 * main
 *********************/
int main(int argc, char * argv[])
{
	if (argc < 2)
		printf("Please specify a destination.\n");
    	int sock;
    	int bytes_read;
	Packet recv_data;
	Packet resp;

    	struct sockaddr_in server_addr , client_addr;
    	socklen_t addr_len;
	//Open socket
        if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
            perror("Socket");
            exit(1);
        }
	// Set address
    	server_addr.sin_family = AF_INET;
    	server_addr.sin_port = htons(5000);
    	server_addr.sin_addr.s_addr = INADDR_ANY;

 	//Bind socket to address
    	if (bind(sock,(struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
    	{
        	perror("Bind");
        	exit(1);
    	}
    	addr_len = sizeof(struct sockaddr);
	
	FILE * dest = fopen(argv[1], "w");
	if (dest == NULL){
		printf("Error opening destination\n");
		exit(1);
	}
		
	printf("\t\t\t\t\t\t\nServer Waiting for client on port 5000\n");
	int seq_ack = 0;
	while (1)
	{
        	//Receive from client
        	bytes_read = recvfrom(sock, &recv_data, sizeof(recv_data), 0, (struct sockaddr *)&client_addr, &addr_len);
	    	
		if (bytes_read == -1){
			perror("recvfrom");
			exit(1);
		}
		// fwrite(recv_data.data, 1, recv_data.header.len, stdout);
		int cksum = recv_data.header.cksum;
		while (1){
			printf("%d %d %d %d %d\n",seq_ack, (recv_data.header.seq_ack),cksum, get_cksum(recv_data), (cksum == get_cksum(recv_data)));
			if (cksum == get_cksum(recv_data) && recv_data.header.seq_ack == seq_ack){
				resp.header.seq_ack = seq_ack;
				resp.header.cksum = get_cksum(resp);	
				if (rand() % 10 != 9){	// Drop 10% of ACK packets
					if(sendto(sock, &resp, sizeof(resp), 0, (struct sockaddr *)&client_addr, addr_len) == -1){
						perror("sendto");
						exit(1);
					}
				}
				break;
			}
			// Send NAK
			else {
			    resp.header.seq_ack = !seq_ack;
			    resp.header.cksum = get_cksum(resp);
			    if (rand() % 10 != 9){	// Drop 10% of ACK packets
				if(sendto(sock, &resp, sizeof(resp), 0, (struct sockaddr *)&client_addr, addr_len) == -1){
					perror("sendto");
					exit(1);
				}
			    }   
			    bytes_read = recvfrom(sock, &recv_data, sizeof(recv_data),0, (struct sockaddr *)&client_addr, &addr_len);
			    cksum = recv_data.header.cksum;
			}
		}
		if (recv_data.header.len == 0) break;		
		seq_ack = !seq_ack;
		// Write packet data
        	printf("Data received! Writing to file... ");
		fwrite(&recv_data.data, recv_data.header.len, 1, dest);
    	}
	fclose(dest);
  	return 0;
}

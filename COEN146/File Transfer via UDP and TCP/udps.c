// Soren Madsen
// Lab 3
// 18 April 2019
// This program is a UDP server to receive and write a file.

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>


/*********************
 * main
 *********************/
int main(int argc, char * argv[])
{
	if (argc < 2)
		printf("Please specify a destination.\n");
    	int sock;
    	int bytes_read;
    	char recv_data[1024];
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
		
	printf("\t\t\t\t\t\t\nUDPServer Waiting for client on port 5000\n");
	while (1)
	{
        	//Receive from client
        	bytes_read = recvfrom(sock,recv_data,1024,0, (struct sockaddr *)&client_addr, &addr_len);
	    	
        	printf("\t\t\t\t Server: The Client (%s , %d) said : ", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
		
		// Write packet data
        	printf("Data received! Writing to file... ");
		fwrite(&recv_data, bytes_read, 1, dest);
		
		if (bytes_read == 0) break;
    	}
	fclose(dest);
  	return 0;
}

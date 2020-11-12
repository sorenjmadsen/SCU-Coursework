// Soren Madsen
// Lab 6
// 18 May 2019
// This program is a Stop and Wait for an Unreliable Channel w/ Loss UDP client that reads from a file.

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <time.h>
#include <fcntl.h>
#include "lab6.h" 	

void send_pkt(int sock, struct sockaddr * server_addr, Packet packet){
	int err = 0;
	err = sendto(sock, &packet, sizeof(packet.header) + packet.header.len, 0, server_addr, sizeof(struct sockaddr)); // send it
	if (err == -1){
		perror("sendto");
		exit(-1);
	}	
}
	
Packet recv_ack(int sock, struct sockaddr * server_addr){
	Packet recv;
	socklen_t addr_len = sizeof(sock);
	recvfrom(sock, &recv,sizeof(recv), 0, (struct sockaddr *)&server_addr, &addr_len);
	return recv;
}

Packet make_packet(char data[10], int len, int seq_ack){
	Header hdr;
	hdr.len = len;
	hdr.seq_ack = seq_ack;

	Packet pkt;
	pkt.header = hdr;
	strcpy(pkt.data, data);

	hdr.cksum = get_cksum(pkt);
	return pkt;
}	


/********************
 * main
 ********************/
int main()
{
    char src_path[1024];

    int sock;
    struct sockaddr_in server_addr;
    struct hostent *host;
    socklen_t addr_len;
    host = (struct hostent *) gethostbyname((char *)"127.0.0.1");

    // Packet vars
    char buffer[SIZE];
    int len;
    int seq_ack = 0;


    // local timer vars
    struct timeval tv;	// timer
    int rv;			// return val


    // open socket
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
	perror("socket");
	exit(1);
    }

    // setup timer with socket
    fd_set readfds;
    fcntl(sock, F_SETFL, O_NONBLOCK);

    // set address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5000);
    server_addr.sin_addr = *((struct in_addr *)host->h_addr);


    printf("Client: Type a filename (OR q/ Q to quit): \t");
    scanf("%s", src_path); //input message

    if ((strcmp(src_path , "q") == 0) || strcmp(src_path, "Q") == 0)
       return 0;

    else {
	FILE * src = fopen(src_path, "r");

	int bytes_read;

	if (src == NULL){
		printf("Error opening source\n");
		exit(1);
	}

	addr_len = sizeof(struct sockaddr);	
	
	Packet packet, recv;	// packet for sending, recv for ACK
	// Loop and send until the file is done.
	while (!feof(src)){
		char buffer[SIZE];
		int len = fread(&buffer, 1, SIZE, src);

		packet = make_packet(buffer, len, seq_ack);
		packet.header.cksum = get_cksum(packet);
		while (1){
			send_pkt(sock, (struct sockaddr *)&server_addr, packet);
			
			// Start timeout process
			FD_ZERO(&readfds);
			FD_SET(sock, &readfds);
			
			// Set the timer
			tv.tv_sec = 1;
			tv.tv_usec = 0;
			
			rv = select(sock + 1, &readfds, NULL, NULL, &tv);
			
			if (rv == -1) perror("select");
			while (rv == 0){
				printf("ACK not received\n");
				send_pkt(sock, (struct sockaddr *)&server_addr, packet);

				// Start timeout process
				FD_ZERO(&readfds);
				FD_SET(sock, &readfds);
			
				// Set the timer
				tv.tv_sec = 1;
				tv.tv_usec = 0;
			
				rv = select(sock + 1, &readfds, NULL, NULL, &tv);			
			}
		
			recv = recv_ack(sock, (struct sockaddr *)&server_addr);
			if (recv.header.seq_ack == seq_ack){
				seq_ack = (packet.header.seq_ack == 0) ? 1 : 0;
				break;
			}
			else {
				printf("Bad ACK\n");
			}
			packet.header.cksum = get_cksum(packet);
		}
	}
	// Send one last empty packet
	
	packet = make_packet("", 0, seq_ack);
	packet.header.cksum = get_cksum(packet);
	send_pkt(sock, (struct sockaddr *)&server_addr, packet);
			
	// Start timeout process
	FD_ZERO(&readfds);
	FD_SET(sock, &readfds);
			
	// Set the timer
	tv.tv_sec = 1;
	tv.tv_usec = 0;
		
	rv = select(sock + 1, &readfds, NULL, NULL, &tv);
		
	if (rv == -1) perror("select");
	int failsafe = 0;
	while (rv == 0){
		if (failsafe >= 3) break;

		send_pkt(sock, (struct sockaddr *)&server_addr, packet);

		// Start timeout process
		FD_ZERO(&readfds);
		FD_SET(sock, &readfds);
			
		// Set the timer
		tv.tv_sec = 1;
		tv.tv_usec = 0;
			
		rv = select(sock + 1, &readfds, NULL, NULL, &tv);
		++failsafe;			
	}
	
	fclose(src);
	printf("All done!\n");
   }

}

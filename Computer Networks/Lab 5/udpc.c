// Soren Madsen
// Lab 5
// 2 May 2019
// This program is a client that sends a file to a UDP server.

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
#include "lab5.h" 	

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


/********************
 * main
 ********************/
int main()
{
int sock;
struct sockaddr_in server_addr;
struct hostent *host;
char src_path[1024];
socklen_t addr_len;
host= (struct hostent *) gethostbyname((char *)"127.0.0.1");

Header header;
header.seq_ack = 1;

Packet packet;
packet.header = header;


// open socket
if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
{
perror("socket");
exit(1);
}

// set address
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(5000);
server_addr.sin_addr = *((struct in_addr *)host->h_addr);

while (1)
{
    printf("Client: Type a filename (OR q/ Q to quit): \t");
    scanf("%s", src_path); //input message

    if ((strcmp(src_path , "q") == 0) || strcmp(src_path, "Q") == 0)
       break;

    else {
	FILE * src = fopen(src_path, "r");

	int bytes_read;

	if (src == NULL){
		printf("Error opening source\n");
		exit(1);
	}

	addr_len = sizeof(struct sockaddr);	
	
	Packet recv;
	packet.header.seq_ack = 0;
	// Loop and send until the file is done.
	while (!feof(src)){
		packet.header.len = fread(&packet.data, 1, SIZE, src);
		packet.header.cksum = get_cksum(packet);

		
		while (1){
			send_pkt(sock, (struct sockaddr *)&server_addr, packet);
			recv = recv_ack(sock, (struct sockaddr *)&server_addr);
			if (recv.header.seq_ack == packet.header.seq_ack){
				packet.header.seq_ack = (packet.header.seq_ack == 0) ? 1 : 0;
				break;
			}
			packet.header.cksum = get_cksum(packet);
		}
	}
	// Send one last empty packet
	

	packet.header.len = 0;
	packet.header.cksum = get_cksum(packet);
	send_pkt(sock, (struct sockaddr *)&server_addr, packet);
	while (1){
		recv = recv_ack(sock, (struct sockaddr *)&server_addr);
		if (recv.header.seq_ack == packet.header.seq_ack && recv.header.cksum == packet.header.cksum) break;
		packet.header.cksum = get_cksum(packet);
	}
	fclose(src);
	printf("All done!\n");
   }

}
}

// Soren Madsen
// Lab 3
// 18 April 2019
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

#define SIZE 40


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

	char buffer[SIZE];
	int bytes_read;

	if (src == NULL){
		printf("Error opening source\n");
		exit(1);
	}
	
	// Loop and send until the file is done.
	while (!feof(src)){
		bytes_read = fread(&buffer, 1, sizeof(buffer), src);
		sendto(sock, buffer, bytes_read, 0,
              		(struct sockaddr *)&server_addr, sizeof(struct sockaddr)); // send it
	}
	// Send one last empty packet
	sendto(sock, NULL, 0, 0,
              		(struct sockaddr *)&server_addr, sizeof(struct sockaddr)); // send it
	fclose(src);
	printf("All done!\n");
   }

}
}

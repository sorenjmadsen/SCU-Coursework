// Soren Madsen
// Lab 3
// 18 April 2019
// This program is a client that sends a read file to a TCP server.

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
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket\n");
		exit(1);
	}

	// set address
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(5000);
	server_addr.sin_addr = *((struct in_addr *)host->h_addr);

	// connect socket
	if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
		perror("failed to connect\n");
		exit(1);
	}
	else {
		printf("connected to the server\n");
	}

    	printf("Client: Type a filename: \t");
    	scanf("%s", src_path); //input message


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
				send(sock, buffer, bytes_read, 0); // send it
			}
			printf("All done!\n");
		fclose(src);
		close(sock);

	
}

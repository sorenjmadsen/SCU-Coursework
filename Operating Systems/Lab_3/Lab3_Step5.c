// Name: Soren Madsen
// Date: 23 Jan 2020
// Title: Lab 3 Step 5
// Description: Simulates producer-consumer communication using pipes

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <sys/wait.h> 
//main
int main() {
 	int fds[2];
 	pipe(fds);
    char buff[60];
    int i, count;

    if (fork() == 0) {
		close(fds[0]);
        printf("Enter message: \n"); 
        fgets(buff, 60, stdin);
        write(fds[1], buff, strlen(buff));
        printf("Producer sent: %s", buff);
        memset(buff, 0, sizeof(char)*60);

	}
    
	else if (fork() == 0) {
		close(fds[1]);
		count = read(fds[0],buff,60);
        printf("Consumer received: %s", buff);
	}
	
	else {  /*parent closes both ends and wait for children*/
		close(fds[0]);
		close(fds[1]);
		wait(0);
		wait(0); 
	}
} 

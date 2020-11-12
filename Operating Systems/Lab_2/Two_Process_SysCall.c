// Name: Soren Madsen
// Date: 16 Jan 2020
// Title: Lab2 - Two Process
// Description: This program functions the same as the Two Process example
// but utilizes a system call to exec( ).

#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */ 
/* main function with command-line arguments to pass */
int main(int argc, char *argv[]) {
    pid_t  pid;
    printf("\n Before forking.\n");
    pid = fork();
    if (pid == -1) {
        fprintf(stderr, "can't fork, error %d\n", errno);
    }    
    else if(pid == 0)
    {
        execlp("/bin/ls", "ls", NULL);
    }
    else
    {
        wait(NULL);
        printf("Child Complete");
        exit(0);
    }

    return 0;
}
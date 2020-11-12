// Name: Soren Madsen
// Date: 16 Jan 2020
// Title: Lab2 - 7 Process Forking
// Description: This program forks until exactly 7 process are made, including the parent.

#include <stdio.h>     /* printf, stderr */
#include <sys/types.h> /* pid_t */
#include <unistd.h>    /* fork */
#include <stdlib.h>    /* atoi */
#include <errno.h>     /* errno */

/* main function with command-line arguments to pass */
int main(int argc, char *argv[])
{
    printf("\n Before forking.\n");
    pid_t pids[6];
    int i;
    printf("Parent\n");
    for (i = 0; i < 6; ++i){
        pids[i] = fork();
        if(pids[i] == -1)
            fprintf(stderr, "can't fork, error %d\n", errno);
        else if (!pids[i]){
            printf("Child #%d\n", i + 1);
        }
        else
        {
            waitpid(pids[i], NULL, 0);
            break;
        }
        
    }




    return 0;
}
// Name: Soren Madsen
// Date: 16 Jan 2020
// Title: Lab2 - Two Threads
// Description: This program performs 100 iterations of print statements
// for each of the two threads (like the process example, but with threads).

#include <stdio.h>   /* printf, stderr */
#include <pthread.h> /* pthread */
#include <stdlib.h>  /* atoi */
#include <errno.h>   /* errno */
/* main function with command-line arguments to pass */

void *thread_start(void * n)
{
    int i, time = *((int *)n);
    free(n);
    for (i = 0; i < 100; i++)
    {
        printf("\t \t \t Second Thread %d \n", i);
        usleep(time);
    }
}

int main(int argc, char *argv[])
{
    pthread_t tid;
    int i, n = atoi(argv[1]); // n microseconds to input from keyboard for delay

    int * n_arg = malloc(sizeof(int));
    *n_arg = n;
    printf("\n Before thread creation.\n");
    pthread_create(&tid, NULL, thread_start, n_arg);

    if (tid == -1) {
        fprintf(stderr, "can't create new thread, error %d\n", errno);
    }  
    // Main thread
    for (i = 0; i < 100; i++)
    {
        printf("Main thread %d\n", i);
        usleep(n);
    }
    pthread_join(tid, NULL);
    return 0;
}
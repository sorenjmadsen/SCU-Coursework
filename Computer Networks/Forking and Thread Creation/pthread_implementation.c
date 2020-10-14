// Soren Madsen
// 4 April 2019
// Lab 1 Part 1
// This program creates a new thread and executes two for loops.

#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <pthread.h>     /* thread */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */ 


void *start_routine (void *n){
    int i;
    for (i = 0; i < 100; ++i){
	printf("\t\t\t\tCreated Thread %d\n", i);
	usleep(*((int *)n));
    }
}

/* main function with command-line arguments to pass */
int main(int argc, char *argv[]) {
    pthread_t tid;
    int i, n = atoi(argv[1]); // n microseconds to input from keyboard for delay
    printf("\n Before creating new thread.\n");
    pthread_create(&tid, NULL, start_routine, &n);
    if (tid == -1) {
        fprintf(stderr, "can't create new thread, error %d\n", errno);
    }    
    // Original Thread 
    for (i=0;i<100;i++) {
        printf("Original thread %d\n",i);
        usleep(n);
    }
    pthread_join(tid, NULL);
    return 0;
}

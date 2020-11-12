// Name: Soren Madsen
// Date: 6 Feb 2020
// Title: Lab 5 - Producer Consumer w/ Semaphores
// Description: This program emulates the producer-consumer relationship while
// protecting shared memory with semaphores.

#include <stdio.h>
#include <unistd.h>
#include <pthread.h> 
#include <semaphore.h> 
#include <fcntl.h>
#include <time.h> 
#include <signal.h>

#define N   10

pthread_t consumer, producer;
sem_t *mutex, *empty, *full;
int buffer[N];
int write_idx = 0;
int read_idx = 0;

void semaphoreUnlinkOnSignal(int code){
    sem_unlink("mutex"); 
    sem_unlink("empty"); 
    sem_unlink("full"); 
    printf("\nUnlinked!\n");
    exit(0);
}

void* produce(void* arg) {  
    int item;
    //Producer thread
    do { 
        // produce next item
        sem_wait(empty);
        sem_wait(mutex);
        item = rand() % 100;
        buffer[write_idx++ % 10] = item;  //add the item to buffer
        printf("Produced: %d\n", item);
        
        sem_post(mutex);
        sem_post(full);
        sleep(1);
    } while (1);
} 

void* consume(void* arg){
    int item;
    //Consumer thread
    do { 
        //consume the item
        sem_wait(full);
        sem_wait(mutex);
        item = buffer[read_idx++ % 10];
        printf("    Consumed: %d\n", item);
        
        sem_post(mutex);
        sem_post(empty);
        sleep(1);
        
    } while (1);
}

int main() { 
    srand(time(NULL));
    signal(SIGINT, semaphoreUnlinkOnSignal);
    mutex = sem_open("mutex", O_CREAT, 0644, 1);
    empty = sem_open("empty", O_CREAT, 0644, N);
    full = sem_open("full", O_CREAT, 0644, 0);
    
    pthread_create(&producer, NULL, produce, NULL);
    sleep(4);
    pthread_create(&consumer, NULL, consume, NULL);

    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);

    sem_unlink("mutex"); 
    sem_unlink("empty"); 
    sem_unlink("full"); 
    
    return 0; 
} 

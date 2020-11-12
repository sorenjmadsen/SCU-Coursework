/*
 * Soren Madsen
 * Lab 9: IO Experimentation
 * 9 March 2020
 * This lab is used to demonstrate the effects of IO on runtime.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Allows us to pass in multiple arguments to each thread
typedef struct {
  int i;
  char **in;
} thread_args;

void *go(void *arg) {
  thread_args args = *((thread_args *)arg);
  
  int count = args.i;
  int len = atoi(args.in[2]);

  int buffer[len];

  char *file = args.in[1];
  FILE *fp = fopen(file, "rb");
  char filename[20];

  // Ensure file copies don't overwrite each other, also mark threads
  sprintf(filename, "thread%d-%s-step4copy-%d.txt", count, file, len);  
  FILE *wp = fopen(filename, "wb");

  while (fread(buffer, len, 1, fp)) {
    fwrite(buffer, len, 1, wp);
  }

  fclose(fp);
  fclose(wp);
}

int main(int argc, char *argv[]) {

  int NTHREADS = atoi(argv[3]);  // Get number of threads
  thread_args args[NTHREADS];

  pthread_t threads[NTHREADS];
  int i;
  

  // Create threads
  for (i = 0; i < NTHREADS; i++) {
    args[i].i = i + 1;
    args[i].in = argv;
    pthread_create(&threads[i], NULL, go, &args[i]);
  }

  // Wait for threads to finish
  for (i = 0; i < NTHREADS; i++) {
    pthread_join(threads[i], NULL);
  }
  return 0;
}
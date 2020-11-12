/*
 * Soren Madsen
 * Lab 9: IO Experimentation
 * 9 March 2020
 * This lab is used to demonstrate the effects of IO on runtime.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_BUF 10000

int main(int argc, char *argv[]) {
  int buffer[MAX_BUF];
  FILE *fp = fopen(argv[1], "rb");
  while (fgets(buffer, MAX_BUF, fp)) {
    // Do nothing
  }  
  fclose(fp);
  return 0;
}
/*
 * Soren Madsen
 * Lab 9: IO Experimentation
 * 9 March 2020
 * This lab is used to demonstrate the effects of IO on runtime.
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int len = atoi(argv[2]);
  int buffer[len];  // Gets buffer size from parameter

  FILE *fp = fopen(argv[1], "rb");

  while (fgets(buffer, len, fp)) {
    // Do nothing
  }

  fclose(fp);
  return 0;
}

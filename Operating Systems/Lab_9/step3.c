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
  char buffer[len];
  FILE *fp = fopen(argv[1], "rb");
  char filename[20];

  // Ensure file copies don't overwrite each other
  sprintf(filename, "%s_step3copy%d.txt", argv[1], len);  
  FILE *wp = fopen(filename, "wb");
  while (fread(buffer, len, 1, fp)) {
    fwrite(buffer, len, 1, wp);
  }
  
  fclose(fp);
  fclose(wp);

  return 0;
}
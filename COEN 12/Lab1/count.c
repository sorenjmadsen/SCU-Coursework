/*
Soren Madsen
COEN 12
Lab 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_WORD_LENGTH 30

int main(int argc, char* argv[]){
    FILE *fp;
    char string[MAX_WORD_LENGTH + 1];
    int count = 0;

    fp = fopen(argv[1], "r");				 // Reads file
    while(!feof(fp)){					 // Loops before end of file
	if (fscanf(fp, "%s", string) == 1) count++;	 // Scans for string
    }
    printf("Total Words: %d\n", count);				 // Print word count
    return 0;
}


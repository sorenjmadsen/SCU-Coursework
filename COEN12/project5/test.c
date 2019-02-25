#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    for (int i = 0; i < 128; i++){
	printf("'%c' Code: %d\n", i, i);
    }
    return 0;
}

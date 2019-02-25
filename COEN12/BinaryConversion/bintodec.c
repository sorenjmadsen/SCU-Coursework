#include <stdio.h>

float binToDec(int bin[8], float x){
    float preDivision = 0;
    int twoTracker = 1;
    for (int i = 7; i >= 0; i--){
	preDivision += bin[i] * twoTracker;
	twoTracker *= 2;
    }
    return (float) preDivision / 128.0;
}

int main(){
    int bit[8] = {1, 0, 1, 0, 0, 0, 0, 0};
    float test;
    test = binToDec(bit, test);
    printf("%f", test);
}

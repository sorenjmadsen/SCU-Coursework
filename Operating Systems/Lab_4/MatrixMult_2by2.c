// Name: Soren Madsen
// Date: 30 Jan 2020
// Title: Lab 4 Step 3
// Description: Multiplies a matrix using a multi-threaded scheme.

#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <pthread.h>

// Max # of Threads allowed was 1023.
#define N 2
#define M 2
#define L 2

double matrixA[N][M], matrixB[M][L], matrixC[N][L];

//void printMatrix(int nr, int nc, double matrix[nr][nc]);
pthread_t tids[N];

void *performRowCalc(void *row){
	int n = (int)(size_t)row;
    int j, k;

	// Free the created pointer
	for(j = 0; j < L; j++)
		for ( k = 0; k < M; k++)
                	matrixC[n][j] += matrixA[n][k] * matrixB[k][j];	
}

int main() {
	
	int i, j, k = 0;
	srand(time(NULL));
	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			matrixA[i][j] = rand() % 10; // rand()
		}
	}

	for (i = 0; i < M; i++) {
		for (j = 0; j < L; j++) {
			matrixB[i][j] = rand() % 10; // rand()
		}
	}
	
	// Multi-Threaded Matrix Multiplication
   	for(i = 0; i < N; i++)
    {
        printf("Thread %d\n", i);
      	pthread_create(&tids[i], NULL, performRowCalc, (void *)(size_t)i);
	}

	for(i = 0; i < N; i++)
		pthread_join(tids[i], NULL);
	
	printf("\n\nMatrixA:\n");
	//printMatrix(N, M, matrixA);
	printf("\n\nMatrixB:\n");
	//printMatrix(M, L, matrixB);
	printf("\n\nMatrixC:\n");
	//printMatrix(N, L, matrixC); 
  return 0;
}
/*
void printMatrix(int nr, int nc, double matrix[nr][nc]) {
	int i,j = 0;
	for (i = 0; i < nr; i++) {
                for (j = 0; j < nc; j ++) {
                        printf("%lf  ", matrix[i][j]);
                }
                printf("\n");
        }
}*/
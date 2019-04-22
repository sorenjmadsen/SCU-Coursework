// Soren Madsen
// 11 April 2019
// Lab 2 Part 1
// This program performs matrix multiplication using multiple threads.

#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <pthread.h>

#define N 512
#define M 1024
#define L 1024

double matrixA[N][M], matrixB[M][L], matrixC[N][L], matrixD[N][L] = {0.0};

void printMatrix(int nr, int nc, double matrix[nr][nc]);
void checkMatrix(int nr, int nc);
pthread_t tids[N];

void *performRowCalc(void *row){
	int n = *((int *) row);
	int j, k = 0;

	// Free the created pointer
	free(row);
	for(j = 0; j < L; j++)
		for ( k = 0; k < M; k++)
                	matrixC[n][j] += matrixA[n][k] * matrixB[k][j];	
}

int main() {
	srand(time(NULL));
	int i, j, k = 0;
	
	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			matrixA[i][j] = rand(); // rand()
		}
	}

	for (i = 0; i < M; i++) {
		for (j = 0; j < L; j++) {
			matrixB[i][j] = rand(); // rand()
		}
	}
	
	// Single Threaded Version
	for(i = 0; i < N; i++)
		for(j = 0; j < L; j++)
			for ( k = 0; k < M; k++)
                		matrixD[i][j] += matrixA[i][k] * matrixB[k][j];
	
	// Multi-Threaded Version
	// NOTE: The matrix was split in half due to the lab machine maximum thread count.
   	for(i = 0; i < N/2; i++){
		// Create a pointer for our row count
		int *arg = malloc(sizeof(int));
		*arg = i;
      		pthread_create(&tids[i], NULL, performRowCalc, arg);
	}

	for(i = 0; i < N/2; i++)
		pthread_join(tids[i], NULL);
	
	for(i = N/2; i < N; i++){
		// Create a pointer for our row count
		int *arg = malloc(sizeof(int));
		*arg = i;
      		pthread_create(&tids[i], NULL, performRowCalc, arg);
	}

	for(i = N/2; i < N; i++)
		pthread_join(tids[i], NULL);
	
	printf("\n\nMatrixA:\n");
	printMatrix(N, M, matrixA);
	printf("\n\nMatrixB:\n");
	printMatrix(M, L, matrixB);
	printf("\n\nMatrixC:\n");
	printMatrix(N, L, matrixC); 
	printf("\n\nMatrixD:\n");
	printMatrix(N, L, matrixD); 
	checkMatrix(N, L);
  return 0;
}

void printMatrix(int nr, int nc, double matrix[nr][nc]) {
	int i,j = 0;
	for (i = 0; i < nr; i++) {
                for (j = 0; j < nc; j ++) {
                        printf("%lf  ", matrix[i][j]);
                }
                printf("\n");
        }
}

void checkMatrix(int nr, int nc){
	int i,j = 0;
	int flag = 0;
	for (i = 0; i < nr; i++) {
                for (j = 0; j < nc; j ++) {
                        if (matrixC[i][j] != matrixD[i][j]){
				flag = 1;
				break;
			}
                }
        }
	printf((flag == 1) ? "\nST and MT do not match\n" : "\n The math checks out!\n");
}

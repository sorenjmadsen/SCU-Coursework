/* matrix.c */

void free(), *malloc();
int printf(), scanf();

int **allocate(int n)
{
    int i;
    int **a;

    a = malloc(n * sizeof a[0]);

    for (i = 0; i < n; i = i + 1)
	a[i] = malloc(n * sizeof a[0][0]);

    return a;
}

int initialize(int **a, int n)
{
    int i, j;


    for (i = 0; i < n; i = i + 1)
	for (j = 0; j < n; j = j + 1)
	    a[i][j] = i + j;
}

int display(int **a, int n)
{
    int i, j;
    int *p;

    i = 0;

    while (i < n) {
	j = 0;

	while (j < n) {
	    p = a[i];
	    printf("%d ", p[j]);
	    j = j + 1;
	}

	i = i + 1;
	printf("\n");
    }
}

int deallocate(int **a, int n)
{
    int i;

    i = 0;

    while (i < n) {
	free(a[i]);
	i = i + 1;
    }

    free(a);
}

int main(void)
{
    int **a;
    int n;

    scanf("%d", &n);
    a = allocate(n);
    initialize(a, n);
    display(a, n);
    deallocate(a, n);
}

/* qsort.c */

int n;
int *a;

void *malloc();
int printf(), scanf();


int readarray(void)
{
    int i;

    i = 0;

    while (i < n) {
	scanf("%d", &a[i]);
	i = i + 1;
    }
}

int writearray(void)
{
    int i;

    i = 0;

    while (i < n) {
	printf("%d ", a[i]);
	i = i + 1;
    }

    printf("\n");
}

int exchange(int *a, int *b)
{
    int t;

    t = *a;
    *a = *b;
    *b = t;
}

int partition(int *a, int y, int z)
{
    int i, j, x;

    x = a[y];
    i = y - 1;
    j = z + 1;

    while (i < j) {
	j = j - 1;

	while (a[j] > x)
	    j = j - 1;

	i = i + 1;

	while (a[i] < x)
	    i = i + 1;

	if (i < j)
	    exchange(&a[i], &a[j]);
    }

    return j;
}


int quicksort(int *a, int m, int n)
{
    int i;

    if (n > m) {
	i = partition(a, m, n);
	quicksort(a, m, i);
	quicksort(a, i + 1, n);
    }
}


int main(void)
{
    n = 8;
    a = malloc(n * sizeof a[0]);
    readarray();
    quicksort(a, 0, n - 1);
    writearray();
}

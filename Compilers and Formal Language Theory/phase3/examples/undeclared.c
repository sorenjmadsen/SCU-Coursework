int f(int x)
{
    x = y;			/* 'y' undeclared */
}


int g(int x, int y)
{
    int z;

    {
	int w;
	x = y + z + p();	/* 'p' undeclared */
    }

    z = w;			/* 'w' undeclared */
}


int x;

char **h(int y)
{
    int z;

    x = y + z + w;		/* 'w' undeclared */
}

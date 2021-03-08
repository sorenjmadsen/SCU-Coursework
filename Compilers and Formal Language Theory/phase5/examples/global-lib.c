/*
 * This file will not be run through your compiler.
 */

# include <stdio.h>

extern void foo();
extern int x, y, z;

int main(void)
{
    foo();
    printf("%d\n", x);
    printf("%d\n", y);
    printf("%d\n", z);
    return 0;
}

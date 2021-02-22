int printf();

int foo(int x, int *y)
{
    int a[10], i, *p;
    char d, *s;


    p = &d;			/* invalid operands to binary = */
    p = &a;			/* lvalue required in expression */
    p = &a[0];
    p = &i;
    x = 0;

    i = d;
    d = i;

    a[1] = i;
    a[p] = i;			/* invalid operands to binary [] */

    x(1);			/* called object is not a function */
    printf("hello world\n");
    s = &d;

    *i = 0;			/* invalid operand to unary * */
    *a = 0;
    p = p + 1;

    i = (p < foo);		/* invalid operands to binary < */

    &x = p;			/* lvalue required in expression */

    foo(d, a);
    foo(1, 2, 3);		/* invalid arguments to called function */
    x = foo(d, a);
    p = foo(d, a);		/* invalid operands to binary = */
}

int x, z;
char y;
char *s, *t;
int *p, *q;
void *v;

int main(void)
{
    x || y && z;
    x && y || x;

    x == y != z;
    x != y == z;

    x < y > z;
    x > y < z;
    x <= y >= z;
    x >= y <= z;

    x + y - z;
    x - y + z;

    x * y / z;
    x / y % z;
    x % y * z;

    p + x + y;
    x + p + y;

    s + x + y;
    x + s + y;

    v + x + y;			/* invalid operands to binary + */
    x + v + y;			/* invalid operands to binary + */

    p + q + x;			/* invalid operands to binary + */
    p + v - x;			/* invalid operands to binary + */

    p - q + x;
    x + p - q;

    s - p + x;			/* invalid operands to binary - */
    s - t - y;

    p - v + x;			/* invalid operands to binary - */
    v - x + y;			/* invalid operands to binary - */

    - x;
    - y;
    - p;			/* invalid operand to unary - */
    - v;			/* invalid operand to unary - */

    ! x;
    ! y;
    ! x * y;
    ! p * y;
    ! v * y;

    &p + x;
    &s - x;
    &v + x;

    x + sizeof p;
    x * sizeof s;
    x * sizeof sizeof v;
}

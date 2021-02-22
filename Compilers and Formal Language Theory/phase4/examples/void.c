int i, j, k;
int *ip, *iq;
void *vp, *vq;

int main(void)
{
    ip == iq;
    vp != vq;
    vp < vp;
    vp < iq;			/* invalid operands to binary < */
    iq > vp;			/* invalid operands to binary > */
    vp + i;			/* invalid operands to binary + */
    vp - vq;			/* invalid operands to binary - */
    ip = ip;
    ip + i;
    *ip;
    *vp;			/* invalid operand to unary * */
}

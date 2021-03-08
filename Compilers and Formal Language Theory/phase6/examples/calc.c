int NUM;
int NL, LPAREN, RPAREN, PLUS, MINUS, STAR, SLASH;
int lookahead, expr();
int c, lexval;

int printf(), exit(), getchar(), isspace(), isdigit();

int lexan(void)
{
    int n;


    if (c == 0)
	c = getchar();

    while (isspace(c) && c != NL)
	c = getchar();

    if (!isdigit(c)) {
	int x;
	x = c;
	c = 0;
	return x;
    }

    n = 0;

    while (isdigit(c)) {
	n = n * 10 + c - 48;
	c = getchar(c);
    }

    lexval = n;
    return NUM;
}


/* Look familiar? */

int match(int token)
{
    if (lookahead != token) {
	printf("syntax error at %d\n", lookahead);
	exit(1);
    }

    lookahead = lexan();
}


int factor(void)
{
    int n;


    if (lookahead == LPAREN) {
	match(LPAREN);
	n = expr();
	match(RPAREN);
	return n;
    }

    n = lexval;
    match(NUM);
    return n;
}


int term(void)
{
    int n;
    
    
    n = factor();

    while (lookahead == STAR || lookahead == SLASH) {
	if (lookahead == STAR) {
	    match(STAR);
	    n = n * factor();

	} else {
	    match(SLASH);
	    n = n / factor();
	}
    }

    return n;
}


int expr(void)
{
    int n;


    n = term();

    while (lookahead == PLUS || lookahead == MINUS) {
	if (lookahead == PLUS) {
	    match(PLUS);
	    n = n + term();

	} else {
	    match(MINUS);
	    n = n - term();
	}
    }

    return n;
}

int main(void)
{
    int n;
    NUM = 256;

    NL = *"\n";
    LPAREN = *"(";
    RPAREN = *")";
    PLUS = *"+";
    MINUS = *"-";
    STAR = *"*";
    SLASH = *"/";

    lookahead = lexan();

    while (lookahead != -1) {
	n = expr();
	printf("%d\n", n);

	while (lookahead == NL)
	    match(NL);
    }
}

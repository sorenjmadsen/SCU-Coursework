/* skeleton code for parser.cpp */
# include <iostream>
# include "lexer.h"
# include "tokens.h"

using namespace std;

int lookahead;
string lexbuf;
void expression();
void expressionList();
void statement();
void declarations();

/* Given Functions */
static void error()
{
	if (lookahead == DONE)
		report("syntax error at end of file");
	else
		report("syntax error at '%s'", lexbuf);

	exit(EXIT_FAILURE);
}

static void match(int t)
{
    // Debug 
    // cout << lookahead << ": " << t << endl;
	if (lookahead != t)
		error();

	lookahead = lexan(lexbuf);
}


/* Expression Parsing */
void primaryExpression()
{
    if (lookahead == LPAREN)
    {
        match(LPAREN);
        expression();
        match(RPAREN);
    }
    else if (lookahead == ID)
    {
        match(ID);
        if (lookahead == LPAREN)
        {
            match(LPAREN);
            if (lookahead != RPAREN)
            {
                expressionList();
            }
            match(RPAREN);
        }
    }
    else if (lookahead == NUM)
    {
        match(NUM);
    }
    else if (lookahead == STRING)
    {
        match(STRING);
    }
}

void postfixExpression()
{
    primaryExpression();
    while (lookahead == LBRACK) {
        match(LBRACK);
        expression();
        match(RBRACK);
        cout << "index" << endl;
        postfixExpression();
    }
}

void prefixExpression()
{
    if (lookahead == AMPERSAND)
    {
        match(AMPERSAND);
        prefixExpression();
        cout << "addr" << endl;
    }
    else if (lookahead == STAR)
    {
        match(STAR);
        prefixExpression();
        cout << "deref" << endl;
    }
    else if (lookahead == EXCLAMATION)
    {
        match(EXCLAMATION);
        prefixExpression();
        cout << "not" << endl;
    }
    else if (lookahead == MINUS)
    {
        match(MINUS);
        prefixExpression();
        cout << "neg" << endl;
    }
    else if (lookahead == SIZEOF)
    {
        match(SIZEOF);
        prefixExpression();
        cout << "sizeof" << endl;
    }
    else
    {
        postfixExpression();
    }
}

void multiplicativeExpression()
{
    prefixExpression();
    while (1)
    {
        if (lookahead == STAR)
        {
            match(STAR);
            prefixExpression();
            cout << "mul" << endl;
        }
        else if (lookahead == SLASH)
        {
            match(SLASH);
            prefixExpression();
            cout << "div" << endl;
        }
        else if (lookahead == PERCENT)
        {
            match(PERCENT);
            prefixExpression();
            cout << "rem" << endl;
        }
        else 
        {
            break;
        }
    }
    
}

void additiveExpression()
{
    multiplicativeExpression();
    while (1)
    {
        if (lookahead == PLUS)
        {
            match(PLUS);
            multiplicativeExpression();
            cout << "add" << endl;
        }
        else if (lookahead == MINUS)
        {
            match(MINUS);
            multiplicativeExpression();
            cout << "sub" << endl;
        }
        else {
            break;
        }
    }
}

void relationalExpression()
{
    additiveExpression();
    while (1)
    {
        if (lookahead == LT)
        {
            match(LT);
            additiveExpression();
            cout << "ltn" << endl;
        }
        else if (lookahead == GT)
        {
            match(GT);
            additiveExpression();
            cout << "gtn" << endl;
        }
        else if (lookahead == LE)
        {
            match(LE);
            additiveExpression();
            cout << "leq" << endl;
        }
        else if (lookahead == GE)
        {
            match(GE);
            additiveExpression();
            cout << "geq" << endl;
        }
        else 
        {
            break;
        }
    }
	return;
}

void equalityExpression()
{
    relationalExpression();
    while (1)
    {
        if (lookahead == EQ)
        {
            match(EQ);
            relationalExpression();
            cout << "eql" << endl;
        }
        else if (lookahead == NE)
        {
            match(NE);
            relationalExpression();
            cout << "neq" << endl;
        }
        else 
        {
            break;
        }
    }
	return;
}

void logicalAndExpression()
{
    equalityExpression();
    while (lookahead == AND)
    {
        match(AND);
        equalityExpression();
        cout << "and" << endl;
    }
	return;
}

void expression()
{
	/* Implement recursive-descent parser.
	 * Check slides to get started.
	 */
    logicalAndExpression();
    while (lookahead == OR)
    {
        match(OR);
        logicalAndExpression();
        cout << "or" << endl;
    }
	return;
}

void expressionList()
{
    expression();
    while (lookahead == ',')
    {
        match(COMMA);
        expression();
    }
}

void assignment()
{
    expression();
    if (lookahead == ASSIGN){
        match(ASSIGN);
        expression();
    }
}

void statements() 
{
    while(lookahead != RBRACE)
    {
        statement();
    }
}

void statement()
{
    if (lookahead == LBRACE){
        match(LBRACE);
        declarations();
        statements();
        match(RBRACE);
    }
    else if (lookahead == RETURN)
    {
        match(RETURN);
        expression();
        match(SEMI);
    }
    else if (lookahead == WHILE)
    {
        match(WHILE);
        match(LPAREN);
        expression();
        match(RPAREN);
        statement();
    }
    else if (lookahead == FOR)
    {
        match(FOR);
        match(LPAREN);
        assignment();
        match(SEMI);
        expression();
        match(SEMI);
        assignment();
        match(RPAREN);
        statement();
    }
    else if (lookahead == IF)
    {
        match(IF);
        match(LPAREN);
        expression();
        match(RPAREN);
        statement();

        if (lookahead == ELSE)
        {
            match(ELSE);
            statement();
        }
    }
    else
    {
        assignment();
        match(SEMI);
    }
}

void pointers()
{
    while(lookahead == STAR)
    {
        match(STAR);
    }
}

void specifier(){
    if (lookahead == INT)
        match(INT);
    else if (lookahead == CHAR)
        match(CHAR);
    else if (lookahead == VOID)
        match(VOID);
}

void declarator()
{
    pointers();
    match(ID);
    if (lookahead == LBRACK)
    {
        match(LBRACK);
        match(NUM);
        match(RBRACK);
    }
}

void declaration()
{
    specifier();
    
    // Declarator List
    declarator();
    while(lookahead == COMMA)
    {
        match(COMMA);
        declarator();
    }
    match(SEMI);
}

void declarations()
{
    while(lookahead == INT || lookahead == NUM || lookahead == VOID)
    {
        declaration();
    }
}

void parameter()
{
    specifier();
    pointers();
    match(ID);
}

void parameterList()
{
    parameter();
    while (lookahead == COMMA)
    {
        match(COMMA);
        parameter();
    }
}

void parameters()
{
    if (lookahead == VOID)
    {
        match(VOID);
    }
    else 
    {
        parameterList();
    }
}

void globalDeclarator()
{
    pointers();
    match(ID);
    if (lookahead == LBRACK)
    {
        match(LBRACK);
        match(NUM);
        match(RBRACK);
    }
    else if (lookahead == LPAREN)
    {
        match(LPAREN);
        match(RPAREN);
    }
}

void remainingDeclarators()
{
    while (lookahead == COMMA)
    {
        match(COMMA);
        globalDeclarator();
    }
    match(SEMI);
}

void functionOrGlobal()
{
    specifier();
    pointers();
    match(ID);
    if (lookahead == LBRACK)
    {
        match(LBRACK);
        match(NUM);
        match(RBRACK);
        remainingDeclarators();
    }
    else if (lookahead == LPAREN)
    {
        match(LPAREN);

        if(lookahead == RPAREN)
        {
            match(RPAREN);
            remainingDeclarators();
        }
        else
        {
            parameters();
            match(RPAREN);
            match(LBRACE);
            declarations();
            statements();
            match(RBRACE);
        }
    }
    else
    {
        remainingDeclarators();
    }
    
}



int main()
{
	lookahead = lexan(lexbuf);

	while (lookahead != DONE)
		functionOrGlobal();

	exit(EXIT_SUCCESS);
}

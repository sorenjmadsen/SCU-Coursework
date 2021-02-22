/*
 * File:	checker.cpp
 *
 * Description:	This file contains the public and private function and
 *		variable definitions for the semantic checker for Simple C.
 *
 *		If a symbol is redeclared, the redeclaration is discarded
 *		and the original declaration is retained.
 *
 *		Extra functionality:
 *		- inserting an undeclared symbol with the error type
 */

# include <iostream>
# include "lexer.h"
# include "checker.h"
# include "tokens.h"
# include "Symbol.h"
# include "Scope.h"
# include "Type.h"


using namespace std;

static Scope *outermost, *toplevel;
static const Type error, integer(INT);

static string redefined = "redefinition of '%s'";
static string redeclared = "redeclaration of '%s'";
static string conflicting = "conflicting types for '%s'";
static string undeclared = "'%s' undeclared";
static string void_object = "'%s' has type void";

static string invalid_operands = "invalid operands to binary %s";
static string invalid_operand = "invalid operand to unary %s";
static string invalid_return = "invalid return type";
static string invalid_type = "invalid type for test expression";
static string not_func = "called object is not a function";
static string invalid_arguments = "invalid arguments to called function";
static string lvalue_required = "lvalue required in expression";

/*
 * Function:	openScope
 *
 * Description:	Create a scope and make it the new top-level scope.
 */

Scope *openScope()
{
    toplevel = new Scope(toplevel);

    if (outermost == nullptr)
	outermost = toplevel;

    return toplevel;
}


/*
 * Function:	closeScope
 *
 * Description:	Remove the top-level scope, and make its enclosing scope
 *		the new top-level scope.
 */

Scope *closeScope()
{
    Scope *old = toplevel;
    toplevel = toplevel->enclosing();
    return old;
}


/*
 * Function:	defineFunction
 *
 * Description:	Define a function with the specified NAME and TYPE.  A
 *		function is always defined in the outermost scope.  This
 *		definition always replaces any previous definition or
 *		declaration.
 */

Symbol *defineFunction(const string &name, const Type &type)
{
    cout << name << ": " << type << endl;
    Symbol *symbol = outermost->find(name);

    if (symbol != nullptr) {
	if (symbol->type().isFunction() && symbol->type().parameters()) {
	    report(redefined, name);
	    delete symbol->type().parameters();

	} else if (type != symbol->type())
	    report(conflicting, name);

	outermost->remove(name);
	delete symbol;
    }

    symbol = new Symbol(name, type);
    outermost->insert(symbol);
    return symbol;
}


/*
 * Function:	declareFunction
 *
 * Description:	Declare a function with the specified NAME and TYPE.  A
 *		function is always declared in the outermost scope.  Any
 *		redeclaration is discarded.
 */

Symbol *declareFunction(const string &name, const Type &type)
{
    cout << name << ": " << type << endl;
    Symbol *symbol = outermost->find(name);

    if (symbol == nullptr) {
	symbol = new Symbol(name, type);
	outermost->insert(symbol);

    } else if (type != symbol->type()) {
	report(conflicting, name);
	delete type.parameters();

    } else
	delete type.parameters();

    return symbol;
}


/*
 * Function:	declareVariable
 *
 * Description:	Declare a variable with the specified NAME and TYPE.  Any
 *		redeclaration is discarded.
 */

Symbol *declareVariable(const string &name, const Type &type)
{
    cout << name << ": " << type << endl;
    Symbol *symbol = toplevel->find(name);

    if (symbol == nullptr) {
	if (type.specifier() == VOID && type.indirection() == 0)
	    report(void_object, name);

	symbol = new Symbol(name, type);
	toplevel->insert(symbol);

    } else if (outermost != toplevel)
	report(redeclared, name);

    else if (type != symbol->type())
	report(conflicting, name);

    return symbol;
}


/*
 * Function:	checkIdentifier
 *
 * Description:	Check if NAME is declared.  If it is undeclared, then
 *		declare it as having the error type in order to eliminate
 *		future error messages.
 */

Symbol *checkIdentifier(const string &name)
{
    Symbol *symbol = toplevel->lookup(name);

    if (symbol == nullptr) {
	report(undeclared, name);
	symbol = new Symbol(name, error);
	toplevel->insert(symbol);
    }

    return symbol;
}

void checkAssignment(const Type &left, const Type &right, const bool &lvalue)
{
    if (left == error || right == error)
        return;

    if(!(lvalue)){
        report(lvalue_required);
        return;
    }
    if (!left.isCompatibleWith(right)){
        report(invalid_operands, "=");
        return;
    }
}

void checkReturnType(const Type &type)
{
    if (type == error)
        return;
    Symbols s = outermost->symbols();
    if(!type.isCompatibleWith(Type(s.back()->type().specifier(), s.back()->type().indirection())))
        report(invalid_return);
}

void checkExpression(const Type &expr, const int &op)
{
    if (expr == error)
        return;
    cout << expr << endl;
    if (!expr.isValue())
        report(invalid_type);
}

Type checkLogical(const Type &left, const Type &right, const string &op)
{
    if (left == error || right == error)
        return error;
    
    if (left.promote().isValue() && right.promote().isValue())
        return integer;
    
    report(invalid_operands, op);
    return error;
}

Type checkEquality(const Type &left, const Type &right, const string &op)
{
    if (left == error || right == error)
        return error;
    
    if(left.promote().isCompatibleWith(right.promote()))
        return integer;
    
    report(invalid_operands, op);
    return error;
}

Type checkRelational(const Type &left, const Type &right, const string &op)
{
    if (left == error || right == error)
        return error;
    
    if(left.promote() == right.promote())
        return integer;
    
    report(invalid_operands, op);
    return error;
}

Type checkAdditive(const Type &left, const Type &right, const string &op)
{
    if (left == error || right == error)
        return error;

    Type leftP = left.promote();
    Type rightP = right.promote();

    if (leftP.isInteger() && rightP.isInteger())
        return integer;

    else if ((leftP.isPointer() && (leftP.specifier() != VOID || leftP.indirection() > 1)) && rightP.isInteger())
        return Type(leftP.specifier(), leftP.indirection());

    else if (op == "+")
    {
        if ((right.isPointer() && (rightP.specifier() != VOID || rightP.indirection() > 1)) && leftP.isInteger())
            return Type(rightP.specifier(), rightP.indirection());
    }
    else if (op == "-")
    {
        if ((rightP.isPointer() && (rightP.specifier() != VOID || rightP.indirection() > 1)) && (leftP.isPointer() && (leftP.specifier() != VOID || leftP.indirection() > 1)) && leftP.specifier() == rightP.specifier())
            return integer;
    }
    report(invalid_operands, op);
    return error;
}

Type checkMultiplicative(const Type &left, const Type &right, const string &op)
{
    if (left == error || right == error)
        return error;
        
    Type leftP = left.promote();
    Type rightP = right.promote();
    if (leftP.isInteger() && rightP.isInteger())
        return integer;

    report(invalid_operands, op);
    return error;
}

Type checkPrefix(const Type &operand, const bool &lvalue, const int &op)
{
    if (operand == error)
        return error;
    if (op == '*')
    {
        Type t = operand.promote();
        if (t.isPointer() && (t.specifier() != VOID || t.indirection() > 1))
            return Type(operand.specifier(), t.indirection() - 1);
        
        report(invalid_operand, "*");
        return error;
    }
    else if (op == '&')
    {
        if (lvalue)
            return Type(operand.specifier(), operand.indirection() + 1);
        
        report(lvalue_required);
        return error;
    }
    else if (op == '!')
    {
        if (operand.isValue())
            return integer;
        
        report(invalid_operand, "!");
        return error;
    }
    else if (op == '-')
    {
        if (operand.promote().isInteger())
            return integer;
        
        report(invalid_operand, "-");
        return error;
    }
    else if (op == SIZEOF)
    {
        if (operand.isValue())
            return integer;
        
        report(invalid_operand, "sizeof");
        return error;
    }
    else
        return error;
}

Type checkPostfix(const Type &left, const Type &expr)
{
    if (left == error || expr == error)
        return error;

    if (left.promote().isPointer() && (left.promote().specifier() != VOID || left.promote().indirection() > 1) && expr.promote().isInteger())
        return Type(left.specifier(), left.promote().indirection() - 1);
    
    report(invalid_operands, "[]");
    return error;
}

Type checkFunctionCall(const Symbol &id, const Parameters &args){
    if(id.type().isError())
        return error;
    if(id.type().isFunction())
    {
        Parameters * tParams = id.type().parameters();
        if (tParams == nullptr)
            return Type(id.type().specifier(), id.type().indirection());
        if (!((*tParams).size() == args.size()))
        {
            report(invalid_arguments);
            return error;
        }
        else if ((*tParams).size() == args.size()){
            for (int i = 0; i < args.size(); ++i){
                if (!(*tParams).at(i).isCompatibleWith(args.at(i)))
                {
                    report(invalid_arguments);
                    return error;
                }     
            }
            return Type(id.type().specifier(), id.type().indirection());
        }
        cout << endl;
        
    }
    report(not_func);
    return error;
}

# include "checker.h"
# include "Scope.h"
# include <iostream>
# include <cstdlib>
using namespace std;

Scope * currentScope = nullptr;

const string e1 = "redefinition of '%s'";
const string e2 = "conflicting types for '%s'";
const string e3 = "redeclaration of '%s'";
const string e4 = "'%s' undeclared";
const string e5 = "'%s' has type void";

void openScope(){
    cout << "open scope" << endl;
    // Open file/global scope
    if (currentScope == nullptr)
        currentScope = new Scope();
        
    // Open function/block scope
    else
    {
        Scope * newScope = new Scope(currentScope);
        currentScope = newScope;
    }
}

void closeScope(){
    cout << "close scope" << endl;
    currentScope = currentScope->enclosing();
}

void declareVariable(string name, Type type)
{
    Symbol * s = currentScope->find(name);
    if (s == nullptr)
    {
        if (type.specifier() == VOID && type.indirection() == 0)
        {
            report(e5, name);
        }
        else 
        {
            s = new Symbol(name, type);
            currentScope->insert(s);
            cout << "declare " << name << " as " << type << endl;
        }
    }
    else if (currentScope->enclosing() != nullptr)
    {
        report(e3, name);
    }
    else if (s->type() != type)
    {
        report(e2, name);
    }
}

void declareFunction(string name, Type type)
{   
    Symbol * s = currentScope->find(name);
    if (s == nullptr)
    {
        s = new Symbol(name, type);
        currentScope->insert(s);
        cout << "declare " << name << " as " << type << endl;
    }
    else if (s->type() != type)
    {
        report(e2, name);
    }
    else if ((s->type()).parameters() != nullptr)
    {
        report(e1, name);
    }
}

void defineFunction(string name, Type type)
{
    Symbol * s = currentScope->find(name);
    if (s == nullptr){
        s = new Symbol(name, type);
        currentScope->insert(s);
        cout << "define " << name << " as " << type << endl;
    }
    else if ((s->type()).parameters() != nullptr)
    {
        report(e1, name);
    }
    else if (s->type() != type)
    {
        report(e2, name);
    } 
}

void checkID(string name)
{
    cout << "check " << name << endl;
    Symbol * s;
    if ((s = currentScope->lookup(name)) == nullptr)
        report(e4, name);
}
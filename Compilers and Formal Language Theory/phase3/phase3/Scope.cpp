# include "Scope.h"
#include <iostream>
using namespace std;

Scope::Scope(Scope * enclosing)
    : _enclosing(enclosing) {}

void Scope::insert(Symbol *symbol)
{
    _symbols.push_back(symbol);
}

Symbol * Scope::find(const string &name) const
{   
    for (u_int i = 0; i < _symbols.size(); ++i)
    {
        if (_symbols[i]->name() == name)
            return _symbols[i];
    }
    return nullptr;
}

Symbol * Scope::lookup(const string &name) const
{
    Symbol *symbol;
    if ((symbol = find(name)) != nullptr)
        return symbol;
    
    return (_enclosing == nullptr) ? nullptr : _enclosing->lookup(name);
}


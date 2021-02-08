#ifndef SCOPE_H
#define SCOPE_H
# include "Symbol.h"
# include "Type.h"

typedef std::vector<Symbol *> Symbols;

class Scope {
    Scope * _enclosing;
    Symbols _symbols;

    public:
        Scope(Scope * enclosing = nullptr);
        void insert(Symbol * symbol);
        Symbol *find(const std::string &name) const;
        Symbol *lookup(const std::string &name) const;

        Scope *enclosing() const { return _enclosing; }
        const Symbols &symbols() const { return _symbols; }
};

#endif
#include <ostream>
#include <vector>

#ifndef TYPE_H
#define TYPE_H
typedef std::vector<class Type> Parameters;

class Type {
    int _specifier;
    unsigned _indirection;
    unsigned _length;
    Parameters * _parameters;
    enum { ARRAY, ERROR, FUNCTION, SCALAR } _kind;

    public:
    Type();
    Type(int specifier, unsigned indirection = 0);
    Type(int specifier, unsigned indirection, unsigned length);
    Type(int specifier, unsigned indirection, Parameters * parameters);

    bool isArray() const { return _kind == ARRAY; }
    bool isError() const { return _kind == ERROR; }
    bool isFunction() const { return _kind == FUNCTION; }
    bool isScalar() const { return _kind == SCALAR; }

    int specifier() const { return _specifier; }
    int indirection() const { return _indirection; }
    int length() const { return _length; } 
    int kind() const { return _kind;}
    Parameters * parameters() const { return _parameters; }

    bool operator==(const Type &rhs) const;
    bool operator!=(const Type &rhs) const;
};

std::ostream &operator <<(std::ostream &ostr, const Type &type);
#endif
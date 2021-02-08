# include "Type.h"
# include "tokens.h"
# include <iostream>

using namespace std;

Type::Type()
    : _kind(ERROR){}

Type::Type(int specifier, unsigned indirection)
    : _specifier(specifier), _indirection(indirection), _kind(SCALAR){}

Type::Type(int specifier, unsigned indirection, unsigned length)
    : _specifier(specifier), _indirection(indirection), _length(length), _kind(ARRAY){}

Type::Type(int specifier, unsigned indirection, Parameters *parameters)
    : _specifier(specifier), _indirection(indirection), _parameters(parameters), _kind(FUNCTION){}

bool Type::operator==(const Type &rhs) const {
    if (_kind != rhs._kind)
        return false;

    if (_kind == ERROR)
        return true;

    if(_specifier != rhs._specifier)
        return false;

    if(_indirection != rhs._indirection)
        return false;

    if(_kind == SCALAR)
        return true;

    if(_kind == ARRAY)
        return _length == rhs._length;

    if(!_parameters || !rhs._parameters)
        return true;

    return *_parameters == *rhs._parameters;
}

bool Type::operator!=(const Type &rhs) const {
    return !(*this == rhs);
}

std::ostream &operator <<(std::ostream &ostr, const Type &type){
    string spec;
    if (type.specifier() == INT)
        spec = "INT";
    else if (type.specifier() == CHAR)
        spec = "CHAR";
    else
        spec = "VOID";
    
    string kind;
    if(type.kind() == 0)
        kind = "ARRAY";
    else if (type.kind() == 1)
        kind = "ERROR";
    else if (type.kind() == 2)
        kind = "FUNCTION";
    else 
        kind = "SCALAR";
    
    return ostr << "(" << spec << ", " << type.indirection() << ", " << kind << ")";
}

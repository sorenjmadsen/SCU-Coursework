# include "Type.h"

class Symbol {
    std::string _name;
    Type _type;

    public:
    Symbol(const std::string &name, const Type &type);
    const std::string name() const{return _name;};
    const Type &type() const{return _type;};
};
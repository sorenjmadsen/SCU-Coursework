/*
 * File:	Register.h
 *
 * Description:	This file contains the class definition for registers on
 *		the Intel 32-bit processor.  Each integer register has two
 *		operand names depending upon the access size.
 */

# ifndef REGISTER_H
# define REGISTER_H
# include <string>
# include <ostream>

class Register {
    typedef std::string string;
    string _name;
    string _byte;

public:
    class Expression *_node;

    Register(const string &name, const string &byte = "");
    const string &name(unsigned size = 0) const;
    const string &byte() const;
};

std::ostream &operator <<(std::ostream &ostr, const Register *reg);

# endif /* REGISTER_H */

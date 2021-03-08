/*
 * File:	Register.cpp
 *
 * Description:	This file contains the member functions for registers on
 *		the Intel 32-bit processor.
 */

# include "Tree.h"
# include "Register.h"

using namespace std;


/*
 * Function:	Register::Register (constructor)
 *
 * Description:	Initialize this register with its correct operand names.
 */

Register::Register(const string &name, const string &byte)
    : _name(name), _byte(byte), _node(nullptr)
{
}


/*
 * Function:	Register::name (accessor)
 *
 * Description:	Return the correct operand name given an access size.
 */

const string &Register::name(unsigned size) const
{
    return size == 1 ? _byte : _name;
}


/*
 * Function:	Register::byte (accessor)
 *
 * Description:	Return the byte operand name for this register.
 */

const string &Register::byte() const
{
    return _byte;
}


/*
 * Function:	operator <<
 *
 * Description:	Write a register to a stream.  The operand name is
 *		determined by the type of the associated expression if
 *		present.  Otherwise, the default name will be used.
 */

ostream &operator <<(ostream &ostr, const Register *reg)
{
    if (reg->_node != nullptr)
	return ostr << reg->name(reg->_node->type().size());

    return ostr << reg->name();
}

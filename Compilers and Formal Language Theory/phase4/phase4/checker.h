/*
 * File:	checker.h
 *
 * Description:	This file contains the public function declarations for the
 *		semantic checker for Simple C.
 */

# ifndef CHECKER_H
# define CHECKER_H
# include "Scope.h"

Scope *openScope();
Scope *closeScope();

Symbol *defineFunction(const std::string &name, const Type &type);
Symbol *declareFunction(const std::string &name, const Type &type);
Symbol *declareVariable(const std::string &name, const Type &type);
Symbol *checkIdentifier(const std::string &name);
void checkAssignment(const Type &left, const Type &right, const bool &lvalue);
void checkReturnType(const Type &type);
void checkExpression(const Type &expr, const int &op);
Type checkLogical(const Type &left, const Type &right, const std::string &op);
Type checkEquality(const Type &left, const Type &right, const std::string &op);
Type checkRelational(const Type &left, const Type &right, const std::string &op);
Type checkAdditive(const Type &left, const Type &right, const std::string &op);
Type checkMultiplicative(const Type &left, const Type &right, const std::string &op);
Type checkPrefix(const Type &operand, const bool &lvalue, const int &op);
Type checkPostfix(const Type &left, const Type &expr);
Type checkFunctionCall(const Symbol &id, const Parameters &args);

# endif /* CHECKER_H */

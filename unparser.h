#ifndef _UNPARSER_H
#define _UNPARSER_H
#include <iostream>
#include "ast.h"

std::string unparseExpression(AST *ast);

void unparseExpr(AST *ast, std::string *s);

void unparseBinExpr(AST *ast, std::string *s);

void unparseArithOp(FILE *out, bin_arith_op op)

void unparseFuncCall(AST *ast, std::string *s);

void unparseIdent(AST *ast, std::string *s);

void unparseNum(AST *ast, std::string *s);




#endif
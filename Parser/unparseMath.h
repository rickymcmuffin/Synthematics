#ifndef _UNPARSEMATH_H
#define _UNPARSEMATH_H
#include "ast.h"


float resultExpression(AST *expression, float xValue);

float resultExpr(AST *expr);

float resultBinExpr(AST *binExpr);

float resultFuncCall(AST *funcCall);

float resultSin(AST *sinFunc);

float resultIdent(AST *ident);

float resultNum(AST *num);

#endif
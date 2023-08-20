#ifndef _UNPARSEMATH_H
#define _UNPARSEMATH_H
#include "AST.h"


float resultExpression(AST *expression, float xValue);

float resultExpr(AST *expr);

float resultBinExpr(AST *binExpr);

float resultFuncCall(AST *funcCall);

float resultIdent(AST *ident);

float resultNum(AST *num);

#endif
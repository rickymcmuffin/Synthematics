#ifndef _UNPARSEMATH_H
#define _UNPARSEMATH_H
#include "ast.h"


double resultExpression(AST *expression, double xValue);
double resultExpression(AST *expression);
double resultExpression(AST *expression, double xValue, double fValue);

double resultExpr(AST *expr);

double resultBinExpr(AST *binExpr);

double resultFuncCall(AST *funcCall);

double resultSin(AST *sinFunc);

double resultPow(AST *powFunc);

double resultMod(AST *modFunc);

double resultSign(AST *signFunc);

double resultAbs(AST *absFunc);

double resultIdent(AST *ident);

double resultNum(AST *num);

#endif
#ifndef _UNPARSEMATH_H
#define _UNPARSEMATH_H
#include "ast.h"
#include <vector>

double resultExpression(AST *expression, double xVal);
double resultExpression(AST *expression);
double resultExpression(AST *expression, double xVal, double fVal);
double resultExpression(AST *expression, double xVal, double fValue, std::vector<AST *> yAux);

double resultExpr(AST *expr);

double resultPeacewise(AST *expr);

bool resultCond(AST *cond);

double resultBinExpr(AST *binExpr);

double resultFuncCall(AST *funcCall);

double resultSin(AST *sinFunc);
double resultCos(AST *cosFunc);

double resultPow(AST *powFunc);

double resultMod(AST *modFunc);

double resultSign(AST *signFunc);

double resultAbs(AST *absFunc);

double resultIdent(AST *ident);

double resultNum(AST *num);

#endif
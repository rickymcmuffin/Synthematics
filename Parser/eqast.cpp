#ifndef _EQAST_H
#define _EQAST_H

#include "eqast.h"

EqAST::EqAST() {
  
}

EqAST::EqAST(std::string s, std::vector<std::string> yAs) {
  mainAST = Parser(s).parseExpression();

  for (int i = 0; i < yAs.size(); i++) {
    AST *yAST = Parser(yAs[i]).parseExpression();
    yAuxes.push_back(yAST);
  }
}

EqAST::~EqAST() { freeAST(mainAST); }

std::string EqAST::toString() { return unparseExpression(mainAST); }

double EqAST::getResult(double xVal, double fValue) {
  return resultExpression(mainAST, xVal, fValue, yAuxes);
}

#endif

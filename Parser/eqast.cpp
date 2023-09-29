#include "eqast.h"

EqAST::EqAST() {}

EqAST::EqAST(std::string s, std::vector<std::string> yAs) {
  mainAST = Parser(s).parseExpression();

  for (int i = 0; i < yAs.size(); i++) {
    AST *yAST = Parser(yAs[i]).parseExpression();
    yAuxes.push_back(yAST);
  }
}

std::string EqAST::toString() { return unparseExpression(mainAST); }

double EqAST::getResult(double xVal, double fValue) {
  return resultExpression(mainAST, xVal, fValue, yAuxes);
}

// yAux is the index of the yAux.
// -1 for mainAST
void EqAST::setExpression(std::string expr, int yAuxInd){
	if(yAuxInd == -1){
		free(mainAST);
		mainAST = Parser(expr).parseExpression();
	} else {
		free(yAuxes[yAuxInd]);
		yAuxes[yAuxInd] = Parser(expr).parseExpression();
	}
}

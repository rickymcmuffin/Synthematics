#include "eqast.h"

EqAST::EqAST(std::string s){
	mainAST = Parser(s).parseExpression();
}

EqAST::~EqAST(){
	freeAST(mainAST);
}

std::string EqAST::toString(){
	return unparseExpression(mainAST);
}

double EqAST::getResult(double xVal, double fValue, std::vector<EqAST> yAuxes){
	return resultExpression(mainAST, xVal, fValue, yAuxes);
}
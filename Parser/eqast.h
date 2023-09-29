#pragma once
#include "ast.h"
#include "parser.h"
#include "unparser.h"
#include "unparseMath.h"
#include <vector>
#include <string>

// This class includes both the main y AST and the yN ASTs
class EqAST{
public:
	EqAST();
	EqAST(std::string expr, std::vector<std::string> yAs);

	std::string toString();


	double getResult(double xVal, double fValue);

	// yAux is the index of the yAux. 
	// -1 for mainAST
	void setExpression(std::string expr, int yAuxInd);


private:
	AST *mainAST;
	std::vector<AST *> yAuxes;
	
};


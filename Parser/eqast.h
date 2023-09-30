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
	EqAST(std::string expr, size_t numYAuxes);
	EqAST(std::string expr, std::vector<std::string> yAs);

	std::string toString();
	std::string toString(size_t yAuxInd);


	double getResult(double xVal, double fValue);
	double getResult(double xVal, double fValue, int yAuxInd);

	// yAux is the index of the yAux. 
	void setExpression(std::string expr, size_t yAuxInd);
	void setExpression(std::string expr);


private:
	AST *mainAST;
	std::vector<AST *> yAuxes;
	
};


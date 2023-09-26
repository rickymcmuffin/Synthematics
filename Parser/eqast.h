#include "ast.h"
#include "parser.h"
#include "unparser.h"
#include "unparseMath.h"

class EqAST{
public:
	EqAST(std::string expr);
	~EqAST();

	std::string toString();


	double getResult(double xVal, double fValue, std::vector<EqAST> yAux);

};
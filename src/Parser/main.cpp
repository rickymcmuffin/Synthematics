#include <iostream>
#include <vector>
#include "parser.h"
#include "unparser.h"
#include "unparseMath.h"

using namespace std;

int main()
{
	Parser p = Parser("y1 +  4");
	Parser y1 = Parser("pow(x,2)");

	try
	{
		AST *expr = p.parseExpression();
		vector<AST *> yAuxes;
		yAuxes.push_back(y1.parseExpression());

		cout << unparseExpression(expr) << endl;

		cout << "result: " << resultExpression(expr, 3, 1, yAuxes) << endl;
	}
	catch (EquationException e)
	{
		cout << e.what() << endl;
	}

	return 0;
}
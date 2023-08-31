#include <iostream>
#include "parser.h"
#include "unparser.h"
#include "unparseMath.h"

using namespace std;

int main()
{
	Parser p = Parser("sin(x)");

	try
	{
		AST *expr = p.parseExpression();
		cout << unparseExpression(expr) << endl;

		cout << resultExpression(expr, 3.14/2) << endl;
	}
	catch (EquationException e)
	{
		cout << e.what() << endl;
	}

	return 0;
}
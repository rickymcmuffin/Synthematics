#include <iostream>
#include "parser.h"
#include "unparser.h"
#include "unparseMath.h"

using namespace std;

int main()
{
	Parser p = Parser("{x <= 0: 2, x > 0: 4}");

	try
	{
		AST *expr = p.parseExpression();
		cout << unparseExpression(expr) << endl;

		cout << "result: " << resultExpression(expr, 3) << endl;
	}
	catch (EquationException e)
	{
		cout << e.what() << endl;
	}

	return 0;
}
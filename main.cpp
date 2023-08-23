#include <iostream>
#include <stdio.h>
#include "equationException.h"
#include "lexer.h"
#include "parser.h"
#include "unparser.h"
#include "unparseMath.h"

using namespace std;

int main()
{

	// try
	// {
	// 	while (!l.isDone())
	// 	{
	// 		token t = l.next();
	// 		cout << t.expression + " | " + to_string(t.index) + " | " + ttyp2str(t.typ) + " | " + t.text + " | " + to_string(t.value) + "\n";
	// 	}
	// }
	// catch (EquationException e)
	// {
	// 	cout << e.what();
	// }

	// string s = "x*x + 2*(x+8)";
	string s = "";
	float xValue = 0;
	cout << "Enter expression: ";

	getline(cin, s);
	
	cout << "Enter x Value: ";

	cin >> xValue;

	try
	{
		Parser p = Parser(s);

		AST *ast = p.parseExpression();

		string unParsed = unparseExpression(ast);

		float result = resultExpression(ast, xValue);
		cout << unParsed << endl;

		cout << result << '\n';
	} catch (EquationException e){
		cout << e.what();
	}


	// cout << "bruh";
	return 0;
}
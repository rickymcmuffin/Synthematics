#include <iostream>
#include <stdio.h>
#include "equationException.h"
#include "Lexer.h"
#include "parser.h"
#include "unparser.h"
#include "unparseMath.h"

using namespace std;

int main()
{
	// std::string s = "4 + 5";
	// Lexer l = Lexer(s);


	// cout << s + "\n";
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

	string s = "-4*(x+x)";

	char expr[100];
	float x;

	cout << "Enter your expression: ";

	// cin.getline(expr, 100);

	cin.getline(expr, 100);

	cout << "Enter your x value: ";

	cin >> x;

	Parser p = Parser(expr);

	AST *ast = p.parseExpression();

	cout << unparseExpression(ast);

	cout << "\n";

	cout << resultExpression(ast, x);


	
	return 0;
}
#include <iostream>
#include <stdio.h>
#include "equationException.h"
#include "Lexer.h"
#include "parser.h"
#include "unparser.h"

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

	string s = "4 + 5";
	Parser p = Parser(s);

	AST *ast = p.parseExpression();

	cout << unparseExpression(ast);
	
	return 0;
}
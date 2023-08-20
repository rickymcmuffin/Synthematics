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
	string s = "7 / x";
	Lexer l = Lexer(s);

	try
	{
		while (!l.isDone())
		{
			token t = l.next();
			cout << t.expression + " | " + to_string(t.index) + " | " + ttyp2str(t.typ) + " | " + t.text + " | " + to_string(t.value) + "\n";
		}
	}
	catch (EquationException e)
	{
		cout << e.what();
	}


	try
	{
		cout << "1\n";
		Parser p = Parser(s);
		cout << "2\n";

		AST *ast = p.parseExpression();
		cout << "3\n";

		string unParsed = unparseExpression(ast);
		cout << "4\n";

		int result = resultExpression(ast, 3);
		cout << unParsed << endl;

		cout << result;
	} catch (EquationException e){
		cout << e.what();
	}

	return 0;
}
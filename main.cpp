#include <iostream>
#include <stdio.h>
#include "equationException.h"
#include "Lexer.h"

using namespace std;

int main()
{
	std::string s = "5*212  + 4(4 abc 3f))";
	Lexer l = Lexer(s);

	cout << s + "\n";
	while (!l.isDone())
	{
		token t = l.next();
		cout << t.expression + " | " + to_string(t.index) + " | " + ttyp2str(t.typ) + " | " + t.text + " | " + to_string(t.value) + "\n";
	}

	return 0;
}
/* $Id: lexer.h,v 1.1 2023/03/08 15:18:43 leavens Exp $ */
#ifndef _LEXER_H
#define _LEXER_H
#include <iostream>
#include <stdbool.h>
#include "token.h"

using namespace std;

class Lexer
{
private:
	string equation;
	int index;
	bool done;


public: 
	
	// Initializes the lexer with a string
	Lexer(string equation);

	// Returns the next token in the string	
	token next();

	// returns true if the lexer is done
	bool isDone();
};

#endif
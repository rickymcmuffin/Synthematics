/* $Id: lexer.h,v 1.1 2023/03/08 15:18:43 leavens Exp $ */
#ifndef _LEXER_H
#define _LEXER_H
#include <iostream>
#include <string>
#include <stdbool.h>
#include "token.h"


class Lexer
{
private:
	std::string expression;
	int currentIndex;
	bool done;

	void consumeIgnored();
	token ident();
	token number();
	std::string afterDot();



public: 
	
	// Initializes the lexer with a string
	Lexer(std::string equation);

	// Returns the next token in the string	
	token next();

	// returns true if the lexer is done
	bool isDone();
};

#endif
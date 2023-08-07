/* $Id: parser.c,v 1.4 2023/03/19 01:17:21 leavens Exp $ */
#include <stdio.h>
#include "parser.h"
#include "equationException.h"

using namespace std;

Parser::Parser(string expression)
{
	Parser::lexer = new Lexer(expression);
	advance();
}

Parser::~Parser()
{
	delete Parser::lexer;
}

void Parser::advance()
{
	if (!lexer->isDone())
	{
		currentTok = lexer->next();
	}
}

void Parser::eat(token_type tt)
{
	if (currentTok.typ == tt)
	{
		advance();
	}
	else
	{
		throw EquationException("Unexpected character", currentTok.index);
	}
}


AST *Parser::parseExpression(){
	
}

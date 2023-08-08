/* $Id: parser.h,v 1.1 2023/03/08 15:18:43 leavens Exp $ */
// This header file defines the externally-visible entry points to the parser
#ifndef _PARSER_H
#define _PARSER_H
#include <iostream>
#include "ast.h"
#include "lexer.h"
#include "token.h"

class Parser
{

public:
	Parser(std::string expression);
	~Parser();

	AST *parseExpression();


private:

	token currentTok;

	Lexer *lexer;

	void advance();

	void eat(token_type tt);

	// <bin-rel-cond> ::= <expr> <rel-op> <expr>
	AST *parseBinRelCond();

	// <rel-op> ::= = | != | < | <= | > | >=
	rel_op parseRelOp();

	// <add-sub-term> ::= <add-sub> <term>
	AST *parseAddSubTerm();

	// <term> ::= <factor> { <mult-div-factor> }
	AST *parseTerm();

	// <mult-div-factor> ::= <mult-div> <factor>
	AST *parseMultDivFactor();

	// <factor> ::= <ident> | <paren-expr> | <signed-number>
	AST *parseFactor();

	// <ident> ( <parameters> )
	AST *parseParameters();

	// <paren-expr> ::= ( <expr> )
	AST *parseParenExpr();

	// <signed-number> ::= + <number> | - <number> | <number>
	AST *parseSignedNumber();
};

#endif
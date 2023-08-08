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

AST *Parser::parseExpression()
{
	token fst = currentTok;
	AST *trm = parseTerm();
	AST *exp = trm;
	while (currentTok.typ == plussym || currentTok.typ == minussym)
	{
		AST *rght = parseAddSubTerm();
		exp = ast_bin_expr(fst, exp, rght->data.op_expr.arith_op,
					    rght->data.op_expr.exp);
	}
	return exp;
}

AST *Parser::parseAddSubTerm()
{

	token opt = currentTok;
	switch (currentTok.typ)
	{
	case plussym:
		eat(plussym);
		AST *exp = parseTerm();
		return ast_op_expr(opt, addop, exp);
		break;
	case minussym:
		eat(minussym);
		AST *e = parseTerm();
		return ast_op_expr(opt, subop, e);
		break;
	default:; // empty statement needed so label isn't immediately
		// followed by a declaration, which is prohibited in C;
		token_type expected[2] = {plussym, minussym};
		throw EquationException("Expected + or -", currentTok.index);
		break;
	}
	// The following should never execute
	return (AST *)NULL;
}

AST *Parser::parseTerm()
{
	token fst = currentTok;
	AST *fac = parseFactor();
	AST *exp = fac;
	while (currentTok.typ == multsym || currentTok.typ == divsym)
	{
		AST *rght = parseMultDivFactor();
		exp = ast_bin_expr(fst, exp, rght->data.op_expr.arith_op,
					    rght->data.op_expr.exp);
	}
	return exp;
}

// <mult-div-factor> ::= <mult-div> <factor>
AST *Parser::parseMultDivFactor()
{
	token opt = currentTok;
	switch (currentTok.typ)
	{
	case multsym:
		eat(multsym);
		AST *exp = parseFactor();
		return ast_op_expr(opt, multop, exp);
		break;
	case divsym:
		eat(divsym);
		AST *e = parseFactor();
		return ast_op_expr(opt, divop, e);
		break;
	default:; // empty statement needed so label isn't immediately
		// followed by a declaration, which is prohibited in C;
		token_type expected[2] = {multsym, divsym};
		throw EquationException("Expected * or /", opt.index);
		break;
	}
	// The following should never execute
	return (AST *)NULL;
}

// <factor> ::= <ident> | <paren-expr> | <signed-number> | <function>
AST *Parser::parseFactor()
{
	token idt;
	switch (currentTok.typ)
	{
	case identsym:; // empty statement needed so label isn't immediately
		// followed by a declaration, which is prohibited in C;
		idt = currentTok;
		eat(identsym);
		AST *iden = ast_ident(idt, idt.text);
		if(currentTok.typ != lparensym){
			return iden;
		}
		return parseParameters();
		break;
	case lparensym:
		return parseParenExpr();
		break;
	case plussym:
	case minussym:
	case numbersym:
		return parseSignedNumber();
		break;
	default:; // empty statement needed so label isn't immediately
		// followed by a declaration, which is prohibited in C;
		token_type expected[5] =
		    {identsym, lparensym, plussym, minussym, numbersym};
		throw EquationException("Expected factor", currentTok.index);
		break;
	}
	// The following should never execute
	return (AST *)NULL;
}

AST_list Parser::parseParameters(){
	eat(lparensym);

	while()

	
}
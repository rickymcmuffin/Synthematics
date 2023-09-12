/* $Id: parser.c,v 1.4 2023/03/19 01:17:21 leavens Exp $ */
#include <stdio.h>
#include "parser.h"
#include "equationException.h"

using namespace std;

// Requires: !ast_list_is_empty(*head) ==> !ast_list_is_empty(*last).
// Requires: when called head points to the first element of an AST_list
// and last points to the last element in that list.
// Modifies *head, *last;
// Splice the list starting at lst into the AST list starting at *head,
// and make *last point to the last element in the resulting list.
static void add_AST_to_end(AST_list *head, AST_list *last, AST_list lst)
{
	if (ast_list_is_empty(*head))
	{
		*head = lst;
		*last = ast_list_last_elem(lst);
	}
	else
	{
		// assert(*last != NULL);
		ast_list_splice(*last, lst);
		*last = ast_list_last_elem(lst);
	}
}

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
	if(fst.typ == lcurlysym){
		return parsePeacewise();
	}
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

AST *Parser::parsePeacewise(){
	token fir = currentTok;
	eat(lcurlysym);

	AST_list condExprs = ast_list_singleton(parseCondExpr());
	AST_list last = condExprs;
	while(currentTok.typ == commasym){
		eat(commasym);
		AST_list newCondExpr = ast_list_singleton(parseCondExpr());
		add_AST_to_end(&condExprs, &last, newCondExpr);
	}

	eat(rcurlysym);
	return ast_peacewise(fir, condExprs);
}

AST *Parser::parseCondExpr(){
	token fir = currentTok;
	AST *cond = parseBinRelCond();

	eat(colonsym);

	AST *expr = parseExpression();

	return ast_cond_expr(fir, cond, expr);
}


// <bin-rel-cond> ::= <expr> <rel-op> <expr>
AST *Parser::parseBinRelCond()
{
	token fir = currentTok;
	AST *leftexp = parseExpression();
	rel_op relop = parseRelOp();
	AST *rightexp = parseExpression();
	return ast_bin_cond(fir, leftexp, relop, rightexp);
}

// <rel-op> ::= = | != | < | <= | > | >=
rel_op Parser::parseRelOp()
{
	cout<< "relop: "<<ttyp2str(currentTok.typ)<<endl;;
	rel_op ret;
	switch (currentTok.typ)
	{
	case eqsym:
		eat(eqsym);
		ret = eqop;
		break;
	case neqsym:
		eat(neqsym);
		ret = neqop;
		break;
	case lessym:
		eat(lessym);
		ret = ltop;
		break;
	case leqsym:
		eat(leqsym);
		ret = leqop;
		break;
	case gtrsym:
		eat(gtrsym);
		ret = gtop;
		break;
	case geqsym:
		eat(geqsym);
		ret = geqop;
		break;
	default:
		throw EquationException("Unexpected token", currentTok.index);
	}

	return ret;
}

AST *Parser::parseAddSubTerm()
{

	token opt = currentTok;
	switch (currentTok.typ)
	{
	case plussym:
	{
		eat(plussym);
		AST *exp = parseTerm();
		return ast_op_expr(opt, addop, exp);
		break;
	}
	case minussym:
	{
		eat(minussym);
		AST *e = parseTerm();
		return ast_op_expr(opt, subop, e);
		break;
	}
	default: // empty statement needed so label isn't immediately
		    // followed by a declaration, which is prohibited in C;
	{
		token_type expected[2] = {plussym, minussym};
		throw EquationException("Expected + or -", currentTok.index);
		break;
	}
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
	{
		eat(multsym);
		AST *exp = parseFactor();
		return ast_op_expr(opt, multop, exp);
		break;
	}
	case divsym:
	{
		eat(divsym);
		AST *e = parseFactor();
		return ast_op_expr(opt, divop, e);
		break;
	}
	default: // empty statement needed so label isn't immediately
		    // followed by a declaration, which is prohibited in C;
	{
		token_type expected[2] = {multsym, divsym};
		throw EquationException("Expected * or /", opt.index);
		break;
	}
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
	case identsym: // empty statement needed so label isn't immediately
				// followed by a declaration, which is prohibited in C;
	{
		idt = currentTok;
		eat(identsym);
		AST *iden = ast_ident(idt, idt.text);
		if (currentTok.typ != lparensym)
		{
			return iden;
			break;
		}
		return parseFunction(idt, iden);
		break;
	}
	case lparensym:
	{
		return parseParenExpr();
		break;
	}
	case plussym:
	case minussym:
	case numbersym:
	{
		return parseSignedNumber();
		break;
	}
	default: // empty statement needed so label isn't immediately
		    // followed by a declaration, which is prohibited in C;
	{
		token_type expected[5] =
		    {identsym, lparensym, plussym, minussym, numbersym};
		throw EquationException("Expected factor", currentTok.index);
		break;
	}
	}
	// The following should never execute
	return (AST *)NULL;
}

AST *Parser::parseFunction(token idt, AST *iden)
{
	func_name func;
	string funcString = idt.text;
	if (funcString.compare("sin") == 0)
	{
		func = sin_f;
	}
	else if (funcString.compare("pow") == 0)
	{
		func = pow_f;
	}
	else if (funcString.compare("mod") == 0)
	{
		func = mod_f;
	}
	else if (funcString.compare("sign") == 0)
	{
		func = sign_f;
	}
	else if (funcString.compare("abs") == 0)
	{
		func = abs_f;
	}
	else
	{
		throw EquationException("unknown function name", idt.index);
	}
	AST_list params = parseParameters();
	return ast_func_call(idt, func, iden, params);
}

AST_list Parser::parseParameters()
{
	eat(lparensym);

	AST_list params = ast_list_empty_list();
	if (currentTok.typ != rparensym)
	{
		params = ast_list_singleton(parseExpression());
		AST_list rest = parseCommaParameters();
		ast_list_splice(params, rest);
	}

	eat(rparensym);

	return params;
}

AST_list Parser::parseCommaParameters()
{
	AST_list ret = ast_list_empty_list();
	AST_list last = ast_list_empty_list();
	while (currentTok.typ == commasym)
	{
		eat(commasym);

		AST_list next = parseExpression();
		add_AST_to_end(&ret, &last, next);
	}

	return ret;
}

// <paren-expr> ::= ( <expr> )
AST *Parser::parseParenExpr()
{
	eat(lparensym);
	AST *expr = parseExpression();
	eat(rparensym);

	return expr;
}

// <signed-number> ::= + <number> | - <number> | <number>
AST *Parser::parseSignedNumber()
{
	token num = currentTok;
	bool isNegative = false;
	if (num.typ == minussym)
	{
		eat(minussym);
		isNegative = true;
	}
	else if (num.typ == plussym)
	{
		eat(plussym);
	}

	double value;

	if (isNegative)
	{
		value = -currentTok.value;
	}
	else
	{
		value = currentTok.value;
	}

	eat(numbersym);
	return ast_number(num, value);
}
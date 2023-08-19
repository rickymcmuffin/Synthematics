#include "unparser.h"

std::string unparseExpression(AST *ast)
{
	std::string ret = "";

	unparseExpr(ast, &ret);


	return ret;
}

void unparseExpr(AST *ast, std::string *s)
{
	printAST(ast);
	switch (ast->type_tag)
	{
	case bin_expr_ast:
		unparseBinExpr(ast, s);
	case func_call_ast:
		unparseFuncCall(ast, s);
	case ident_ast:
		unparseIdent(ast, s);
	case number_ast:
		unparseNum(ast, s);
	}
}

void unparseBinExpr(AST *ast, std::string *s)
{	
	
	std::cout << *s + " bruh2\n";
	*s += '(';

	unparseExpr(ast->data.bin_expr.leftexp, s);

	unparseArithOp(ast->data.bin_expr.arith_op, s);

	unparseExpr(ast->data.bin_expr.rightexp, s);

	*s += ')';
}

// Unparse the given bin_arith_opo to out
void unparseArithOp(bin_arith_op op, std::string *s)
{
	switch (op)
	{
	case addop:
		*s += '+';
		break;
	case subop:
		*s += '-';
		break;
	case multop:
		*s += '*';
		break;
	case divop:
		*s += '/';
		break;
	default:
		break;
	}
}

void unparseFuncCall(AST *ast, std::string *s)
{	
	std::cout << *s + " bruh\n";
	unparseIdent(ast->data.func_call.identifier, s);

	*s += '(';

	unparseParameters(ast->data.func_call.parameters, s);

	*s += ')';

	
}

void unparseParameters(AST_list al, std::string *s){
	if(!ast_list_is_empty(al)){
		unparseExpr(ast_list_first(al), s);
		al = ast_list_rest(al);
	}
	while(!ast_list_is_empty(al)){
		*s += ',';
		unparseExpr(ast_list_first(al), s);
		al = ast_list_rest(al);
	}
}

void unparseIdent(AST *ast, std::string *s)
{
	*s += ast->data.ident.name;
}

void unparseNum(AST *ast, std::string *s)
{
	std::cout << *s + " first\n";
	*s += std::to_string(ast->data.number.value);
	std::cout << *s + " last\n";
}
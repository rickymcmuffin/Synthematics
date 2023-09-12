#include "unparser.h"
#include <sstream>
#include <iomanip>

using namespace std;

std::string unparseExpression(AST *ast)
{
	std::string ret = "";

	unparseExpr(ast, &ret);

	return ret;
}

void unparseExpr(AST *ast, std::string *s)
{
	if (ast == NULL)
	{
		return;
	}
	switch (ast->type_tag)
	{
	case peacewise_ast:
		unparsePeacewise(ast, s);
		break;
	case bin_expr_ast:
		unparseBinExpr(ast, s);
		break;
	case func_call_ast:
		unparseFuncCall(ast, s);
		break;
	case ident_ast:
		unparseIdent(ast, s);
		break;
	case number_ast:
		unparseNum(ast, s);
		break;
	default:
		break;
	}
}

void unparsePeacewise(AST *ast, std::string *s)
{
	*s += "{";

	AST_list condExprs = ast->data.peacewise.cond_exprs;

	unparseCondExpr(ast_list_first(condExprs), s);

	condExprs = ast_list_rest(condExprs);

	while (!ast_list_is_empty(condExprs))
	{
		*s += ", ";
		unparseCondExpr(ast_list_first(condExprs), s);

		condExprs = ast_list_rest(condExprs);
	}

	*s += "}";
}

void unparseCondExpr(AST *ast, std::string *s)
{
	unparseBinCond(ast->data.cond_expr.cond, s);

	*s += ": ";

	unparseExpr(ast->data.cond_expr.expr, s);
}

void unparseBinCond(AST *ast, std::string *s)
{
	unparseExpr(ast->data.bin_cond.leftexp, s);

	switch (ast->data.bin_cond.relop)
	{
	case eqop:
		*s += " = ";
		break;
	case neqop:
		*s += " != ";
		break;
	case ltop:
		*s += " < ";
		break;
	case leqop:
		*s += " <= ";
		break;
	case gtop:
		*s += " > ";
		break;
	case geqop:
		*s += " >= ";
		break;
	}

	unparseExpr(ast->data.bin_cond.rightexp, s);
}

void unparseBinExpr(AST *ast, std::string *s)
{

	*s += '(';

	unparseExpr(ast->data.bin_expr.leftexp, s);

	*s += ' ';

	unparseArithOp(ast->data.bin_expr.arith_op, s);

	*s += ' ';

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
	unparseIdent(ast->data.func_call.identifier, s);

	*s += '(';

	unparseParameters(ast->data.func_call.parameters, s);

	*s += ')';
}

void unparseParameters(AST_list al, std::string *s)
{
	if (!ast_list_is_empty(al))
	{
		unparseExpr(ast_list_first(al), s);
		al = ast_list_rest(al);
	}
	while (!ast_list_is_empty(al))
	{
		*s += ", ";
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
	std::stringstream stream;
	stream << std::setprecision(3) << ast->data.number.value;
	*s += stream.str();
	// *s += std::to_string( ast->data.number.value);
}
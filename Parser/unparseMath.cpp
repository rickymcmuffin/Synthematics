#include "unparseMath.h"
#include "equationException.h"
#include <cmath>

float xValue;

float resultExpression(AST *expression, float xVal)
{
	xValue = xVal;

	return resultExpr(expression);
}

float resultExpr(AST *expr)
{

	float res = 0;
	switch (expr->type_tag)
	{
	case bin_expr_ast:
		res = resultBinExpr(expr);
		break;
	case func_call_ast:
		res = resultFuncCall(expr);
		break;
	case ident_ast:
		res = resultIdent(expr);
		break;
	case number_ast:
		res = resultNum(expr);
		break;
	}

	return res;
}

float resultBinExpr(AST *binExpr)
{
	float left = resultExpr(binExpr->data.bin_expr.leftexp);

	float right = resultExpr(binExpr->data.bin_expr.rightexp);

	float res = 0;
	switch (binExpr->data.bin_expr.arith_op)
	{
	case addop:
		res = left + right;
		break;
	case subop:
		res = left - right;
		break;
	case multop:
		res = left * right;
		break;
	case divop:
		res = left / right;
		break;
	}

	return res;
}

float resultFuncCall(AST *funcCall)
{

	switch (funcCall->data.func_call.func)
	{
	case sin_f:
		return resultSin(funcCall);
		break;
	default:
		throw EquationException("Unrecognized function", funcCall->index);
	}
	return 0;
}

float resultSin(AST *sinFunc){
	AST *param = ast_list_first(sinFunc->data.func_call.parameters);
	float exprResult = resultExpr(sinFunc->data.func_call.parameters);

	return sin(exprResult);

}

float resultIdent(AST *ident)
{
	string str(ident->data.ident.name);
	if (str != "x")
	{
		throw EquationException("Unknown variable: " + str, ident->index);
	}

	return xValue;
}

float resultNum(AST *num)
{
	return num->data.number.value;
}
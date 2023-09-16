/* $Id: ast.c,v 1.9 2023/03/23 05:36:03 leavens Exp $ */
#include <stdlib.h>
// #include <cstring>
#include <string>
#include "equationException.h"
#include "ast.h"

// Return a (pointer to a) fresh AST
// and fill in its file_location with the given file name (fn),
// line number (ln) and column number (col).
// Also initializes the next pointer to NULL.
// If there is no space to allocate an AST node,
// print an error on stderr and exit with a failure code.
static AST *ast_allocate(unsigned int ind)
{
    AST *ret = (AST *)malloc(sizeof(AST));
    if (ret == NULL)
    {
        throw EquationException("No space to create an AST!", 0);
    }
    ret->index = ind;
    ret->next = NULL;

    return ret;
}

extern AST *ast_peacewise(token t, AST_list cond_exprs){
    AST *ret = ast_allocate(t.index);
    ret->type_tag = peacewise_ast;
    ret->data.peacewise.cond_exprs = cond_exprs;
    return ret;
}

extern AST *ast_cond_expr(token t, AST *cond, AST *expr){
    AST *ret = ast_allocate(t.index);
    ret->type_tag = cond_expr_ast;
    ret->data.cond_expr.cond = cond;
    ret->data.cond_expr.expr = expr;
    return ret;
}

// Return a (pointer to a) fresh AST for an odd condition
// with expression AST exp
AST *ast_odd_cond(token t, AST *exp)
{
    AST *ret = ast_allocate(t.index);
    ret->type_tag = odd_cond_ast;
    ret->data.odd_cond.exp = exp;
    return ret;
}

// Return a (pointer to a) fresh AST for a binary condition
// with left expression AST e1, relational operator relop,
// and right expression e2
AST *ast_bin_cond(token t, AST *e1, rel_op relop, AST *e2)
{
    AST *ret = ast_allocate(t.index);
    ret->type_tag = bin_cond_ast;
    ret->data.bin_cond.leftexp = e1;
    ret->data.bin_cond.relop = relop;
    ret->data.bin_cond.rightexp = e2;
    return ret;
}

// Return a (pointer to a) fresh AST for a pair of a binary operator, op,
// and a (right) expression e2
AST *ast_op_expr(token t, bin_arith_op op, AST *e2)
{
    AST *ret = ast_allocate(t.index);
    ret->data.op_expr.arith_op = op;
    ret->data.op_expr.exp = e2;
    return ret;
}

// Return a (pointer to a) fresh AST for a binary expression
// with left expresion AST e1, binary artihmetic operator arith_op,
// and right expression AST e2.
AST *ast_bin_expr(token t, AST *e1, bin_arith_op arith_op, AST *e2)
{
    AST *ret = ast_allocate(t.index);
    ret->type_tag = bin_expr_ast;
    ret->data.bin_expr.leftexp = e1;
    ret->data.bin_expr.arith_op = arith_op;
    ret->data.bin_expr.rightexp = e2;
    return ret;
}

// Return a (pointer to a) fresh AST for a function call
// with function identifier AST ident and list of parameters.
extern AST *ast_func_call(token t, func_name func, AST *ident, AST_list param)
{
    AST *ret = ast_allocate(t.index);
    ret->type_tag = func_call_ast;
    ret->data.func_call.func = func;
    ret->data.func_call.identifier = ident;
    ret->data.func_call.parameters = param;
    return ret;
}

// Return a (pointer to a) fresh AST for an identref expression
// with the given name.
AST *ast_ident(token t, std::string str)
{
    AST *ret = ast_allocate(t.index);
    ret->type_tag = ident_ast;
    char *arr = new char[str.length() + 1];
    strcpy(arr, str.c_str());
    ret->data.ident.name = arr;

    ret->data.ident.yAux = -1;
    if(str.at(0) == 'y'){
        try{
            ret->data.ident.yAux = std::stoi(str.substr(1,str.length()));
        } catch(std::invalid_argument e){
        }
    }
    return ret;
}

// Return a (pointer to a) fresh AST for an (signed) number expression
// with the given value
AST *ast_number(token t, double value)
{
    AST *ret = ast_allocate(t.index);
    ret->type_tag = number_ast;
    ret->data.number.value = value;
    return ret;
}

// Return an AST list that is empty
AST_list ast_list_empty_list()
{
    return NULL;
}

// Return an AST list consisting of just the given AST node (ast)
AST_list ast_list_singleton(AST *ast)
{
    return ast;
}

// Return true just when lst is an empty list (and false otherwise)
bool ast_list_is_empty(AST_list lst)
{
    return lst == NULL;
}

// Requires lst != NULL
// Return the first element in an AST_list
AST *ast_list_first(AST_list lst)
{
    // each node is an AST itself, so the first element is lst
    return lst;
}

// Requires lst != NULL
// Return the rest of the AST_list (which is null if it is empty)
AST_list ast_list_rest(AST_list lst)
{
    return lst->next;
}

// Return the last element in the AST list lst.
// The result is only NULL if ast_list_is_empty(lst);
AST_list ast_list_last_elem(AST_list lst)
{
    AST *prev = NULL;
    while (!ast_list_is_empty(lst))
    {
        prev = lst;
        lst = ast_list_rest(lst);
    }
    // here ast_list_is_empty(lst)
    return prev;
}

// Requires: !ast_list_is_empty(lst) and ast_list_is_empty(ast_list_rest(lst))
// Make newtail the tail of the AST_list starting at lst
void ast_list_splice(AST_list lst, AST_list newtail)
{
    lst->next = newtail;
}

// Return the number of elements in the AST list lst.
extern int ast_list_size(AST_list lst)
{
    int ret = 0;
    while (!ast_list_is_empty(lst))
    {
        ret++;
        lst = ast_list_rest(lst);
    }
    return ret;
}

static std::string atstrs[7] = {
    "odd_cond_ast",
    "bin_cond_ast",
    "op_expr_ast",
    "bin_expr_ast",
    "func_call_ast",
    "ident_ast",
    "number_ast"

};

std::string astTypeToString(AST_type type){
    return atstrs[type];
}

extern void printAST(AST *ast)
{
    std::cout << astTypeToString(ast->type_tag) + '\n';

}
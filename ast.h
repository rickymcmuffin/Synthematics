/* $Id: ast.h,v 1.9 2023/03/23 05:23:01 leavens Exp $ */
#ifndef _AST_H
#define _AST_H
#include <iostream>
#include <stdbool.h>
#include "token.h"

// types of ASTs (type tags)
typedef enum
{
    odd_cond_ast,
    bin_cond_ast,
    op_expr_ast,
    bin_expr_ast,
    func_call_ast,
    ident_ast,
    number_ast
} AST_type;

// forward declaration, so can use the type AST* below
typedef struct AST_s AST;
// lists of ASTs
typedef AST *AST_list;

// The following types for structs named N_t
// are used in the declaration of the AST_s struct below.
// The struct N_t is the type of information kept in the AST
// that is related to the nonterminal N in the abstract syntax.
// In addition there are two enum types declared before AST_s,
// one for relational operators (rel_op, which is used in the type cond_t,
// which is the struct related to the ASTs for <condition>)
// and one for binary arithmetic operators (bin_arith_op, which is used in
// the types op_expr_t and bin_exp_t, the latter being
// the struct related to the ASTs for <expr>).

// r ::= = | != | < | <= | > | >=
typedef enum
{
    eqop,
    neqop,
    ltop,
    leqop,
    gtop,
    geqop
} rel_op;

// C ::= odd E
typedef struct
{
    AST *exp;
} odd_cond_t;

// C ::= E1 r E2
typedef struct
{
    AST *leftexp;
    rel_op relop;
    AST *rightexp;
} bin_cond_t;

// o ::= + | - | * | /
typedef enum
{
    addop,
    subop,
    multop,
    divop
} bin_arith_op;

// E ::= o E
// The following is used for pairs of operator and an expression
// (when parsing terms and factors),
// but it is converted into some other kind of AST eventually
typedef struct
{
    bin_arith_op arith_op;
    AST *exp;
} op_expr_t;

// E ::= E o E
typedef struct
{
    AST *leftexp;
    bin_arith_op arith_op;
    AST *rightexp;
} bin_expr_t;

typedef struct
{
    AST *identifier;
    AST_list parameters;
} func_call_t;

// E ::= x
// The ident_t struct holds intermediate representation information
// as well as the syntactic information. That is, parts of the
// idu field will be filled in during static analysis.
typedef struct
{
    // name of a constant or variable
    std::string name;
} ident_t;

// E ::= n
typedef struct
{
    short int value;
} number_t;

// The actual AST definition:
typedef struct AST_s
{
    int index;
    AST_list next; // for lists
    AST_type type_tag;
    union AST_u
    {
        odd_cond_t odd_cond;
        bin_cond_t bin_cond;
        op_expr_t op_expr;
        bin_expr_t bin_expr;
        func_call_t func_call;
        ident_t ident;
        number_t number;
    } data;
} AST;

// Return a (pointer to a) fresh AST for an odd condition
// with expression AST exp
extern AST *ast_odd_cond(token t, AST *exp);

// Return a (pointer to a) fresh AST for a binary condition
// with left expression AST e1, relational operator relop,
// and right expression e2
extern AST *ast_bin_cond(token t, AST *e1, rel_op relop, AST *e2);

// Return a (pointer to a) fresh AST for a pair of a binary operator, op,
// and a (right) expression e2
extern AST *ast_op_expr(token t, bin_arith_op op, AST *e2);

// Return a (pointer to a) fresh AST for a binary expression
// with left expresion AST e1, binary artihmetic operator arith_op,
// and right expression AST e2.
extern AST *ast_bin_expr(token t, AST *e1, bin_arith_op arith_op, AST *e2);

// Return a (pointer to a) fresh AST for a function call
// with function identifier AST ident and list of parameters.
extern AST *ast_func_call(token t, AST *ident, AST_list param);

// Return a (pointer to a) fresh AST for an ident expression
// with the given name.
extern AST *ast_ident(token t, std::string name);

// Return a (pointer to a) fresh AST for an (signed) number expression
// with the given value
extern AST *ast_number(token t, short int value);

// Return an AST list that is empty
extern AST_list ast_list_empty_list();

// Return an AST list consisting of just the given AST node (ast)
extern AST_list ast_list_singleton(AST *ast);

// Return true just when lst is an empty list (and false otherwise)
extern bool ast_list_is_empty(AST_list lst);

// Requires: !ast_list_is_empty(lst)
// Return the first element in an AST_list
extern AST *ast_list_first(AST_list lst);

// Requires: !ast_list_is_empty(lst)
// Return the rest of the AST_list (which is null if it is empty)
extern AST_list ast_list_rest(AST_list lst);

// Requires: !ast_list_is_empty(lst) and ast_list_is_empty(ast_list_rest(lst))
// Make newtail the tail of the AST_list starting at lst
extern void ast_list_splice(AST_list lst, AST_list newtail);

// Return the last element in the AST list lst.
// The result is only NULL if ast_list_is_empty(lst);
extern AST_list ast_list_last_elem(AST_list lst);

// Return the number of elements in the AST list lst.
extern int ast_list_size(AST_list lst);

#endif
/* $Id: token.h,v 1.1 2023/03/08 15:18:43 leavens Exp $ */
#ifndef _TOKEN_H
#define _TOKEN_H

#define MAX_IDENT_LENGTH 255

#include <iostream>

// types of tokens
typedef enum {
    lparensym, rparensym, lcurlysym, rcurlysym, colonsym, commasym,
    identsym, numbersym, doublesym,
    eqsym, neqsym, lessym, leqsym, gtrsym, geqsym, 
    plussym, minussym, multsym, divsym, powsym, eofsym 
} token_type;

// information about each token
typedef struct token {
    token_type typ;
    std::string expression;
    unsigned int index;
    std::string text; // non-NULL, if applicable
    double value; // when typ==numbersym, its value
} token;

// Return the name of the token_type enum
// corresponding to the given token_type value
extern std::string ttyp2str(token_type ttyp);

#endif
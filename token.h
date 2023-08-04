/* $Id: token.h,v 1.1 2023/03/08 15:18:43 leavens Exp $ */
#ifndef _TOKEN_H
#define _TOKEN_H

#define MAX_IDENT_LENGTH 255

// types of tokens
typedef enum {
    lparensym, rparensym,
    identsym, numbersym, 
    eqsym, neqsym, lessym, leqsym, gtrsym, geqsym, 
    plussym, minussym, multsym, divsym, 
} token_type;

// information about each token
typedef struct token {
    token_type typ;
    const char *filename;
    unsigned int line;
    unsigned int column;
    char *text; // non-NULL, if applicable
    short int value; // when typ==numbersym, its value
} token;

// Return the name of the token_type enum
// corresponding to the given token_type value
extern const char *ttyp2str(token_type ttyp);

#endif
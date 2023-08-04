/* $Id: lexer.h,v 1.1 2023/03/08 15:18:43 leavens Exp $ */
#ifndef _LEXER_H
#define _LEXER_H
#include <stdbool.h>
#include "token.h"

// Requires: fname != NULL
// Requires: fname is the name of a readable file
// Initialize the lexer and start it reading
// from the given file name
extern token *lexer_lex(const char *expression);

// Close the file the lexer is working on
// and make this lexer be done
extern void lexer_close();

// Is the lexer's token stream finished
// (either at EOF or not open)?
extern bool lexer_done();

// Requires: !lexer_done()
// Return the next token in the input file,
// advancing in the input
extern token lexer_next();

// Requires: !lexer_done()
// Return the name of the current file
extern const char *lexer_filename();

// Requires: !lexer_done()
// Return the line number of the next token
extern unsigned int lexer_line();

// Requires: !lexer_done()
// Return the column number of the next token
extern unsigned int lexer_column();
#endif
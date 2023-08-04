#include "token.h"

// Translation from enum values to strings
static const char *ttstrs[34] =
    {"lparensym", "rparensym",
    "identsym", "numbersym", 
    "eqsym", "neqsym", "lessym", "leqsym", "gtrsym", "geqsym", 
    "plussym", "minussym", "multsym", "divsym"};

// Return the name of the token_type enum
// corresponding to the given token_type value
const char *ttyp2str(token_type ttyp)
{
    return ttstrs[ttyp];
}
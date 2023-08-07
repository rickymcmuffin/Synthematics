#include "token.h"

// Translation from enum values to strings
static std::string ttstrs[34] =
    {"lparensym", "rparensym", "lcurlysym", "rcurlysym", "colonsym", "commasym",
    "identsym", "numbersym", "doublesym",
    "eqsym", "neqsym", "lessym", "leqsym", "gtrsym", "geqsym", 
    "plussym", "minussym", "multsym", "divsym", "powsym", "eofsym"};

// Return the name of the token_type enum
// corresponding to the given token_type value
extern std::string ttyp2str(token_type ttyp)
{
    return ttstrs[ttyp];
}
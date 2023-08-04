#include "lexer.h"
#include <stdlib.h>
#include <ctype.h>



token *lexer_lex(const char *expression){

	int expressionSize = sizeof(expression)/sizeof(char);



}

void consumeIgnored(const char *expression, int *curIndex){
	while(isspace(expression[*curIndex])){
		*curIndex++;
	}
}

token lexer_ident(const char *expression, int *curIndex){
	char *text = (char*) malloc((MAX_IDENT_LENGTH+1) *sizeof(char));

	int n = 0;
	char c = expression[*curIndex];
	while(isdigit(c)||isalpha(c)){
		if(n >= MAX_IDENT_LENGTH){
			
		}

		text[n] = c;

	}
}

token lexer_next(const char *expression, int *curIndex){
	consumeIgnored(expression, curIndex);	
	token ret;

	ret.expression = expression;
	ret.index = *curIndex;
	ret.text = nullptr;
	ret.value = 0;


	switch (expression[*curIndex]){
		case '\0':
			ret.typ = eofsym;
			break;
		case '(':
			ret.typ = lparensym;
			break;
		case ')':
			ret.typ = rparensym;
			break;
		
	}
}
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "equationException.h"

using namespace std;

Lexer::Lexer(std::string expression)
{
	this->expression = expression;
	this->done = false;
	this->currentIndex = 0;
}

void Lexer::consumeIgnored()
{
	while (isspace(expression[currentIndex]))
	{
		currentIndex++;
	}
}

token Lexer::ident()
{
	token ret;
	ret.typ = identsym;
	ret.expression = expression;
	ret.index = currentIndex;
	ret.value = 0;
	ret.text = "";

	char c = expression[currentIndex];
	int n = 0;
	while (isdigit(c) || isalpha(c))
	{
		if (n >= MAX_IDENT_LENGTH)
		{
			throw EquationException("Identifier too long", currentIndex);
		}

		ret.text += c;
		currentIndex++;
		c = expression[currentIndex];
	}

	return ret;
}

token Lexer::number()
{
	token ret;
	ret.typ = numbersym;
	ret.expression = expression;
	ret.index = currentIndex;
	ret.value = 0;
	ret.text = "";

	bool hasSeenDot = false;
	char c = expression[currentIndex];
	int n = 0;
	while (isdigit(c) || c == '.')
	{
		if(c == '.'){
			if(hasSeenDot)
				throw EquationException("Expected number", currentIndex);
			hasSeenDot = true;
		}
		if (n >= MAX_IDENT_LENGTH)
		{
			throw EquationException("Identifier too long", currentIndex);
		}

		ret.text += c;
		currentIndex++;
		c = expression[currentIndex];
	}
	ret.value = stof(ret.text);

	return ret;
}


token Lexer::next()
{
	consumeIgnored();
	char c = expression[currentIndex];
	token ret;

	ret.expression = expression;
	ret.index = currentIndex;
	ret.text = c;
	ret.value = 0;

	if (isalpha(c))
	{
		return ident();
	}
	if (isdigit(c))
	{
		return number();
	}

	switch (expression[currentIndex])
	{
	case '\0':
		done = true;
		ret.typ = eofsym;
		break;
	case '(':
		ret.typ = lparensym;
		break;
	case ')':
		ret.typ = rparensym;
		break;
	case '{':
		ret.typ = lcurlysym;
		break;
	case '}':
		ret.typ = rcurlysym;
		break;
	case ':':
		ret.typ = colonsym;
		break;
	case ',':
		ret.typ = commasym;
		break;
	case '=':
		ret.typ = eqsym;
		break;
	case '!':
		if (expression[currentIndex + 1] != '=')
		{
			throw EquationException("Expected =", currentIndex + 1);
		}
		ret.text += expression[currentIndex + 1];
		currentIndex++;
		ret.typ = neqsym;
		break;
	case '<':
		if (expression[currentIndex + 1] == '=')
		{
			ret.text += expression[currentIndex + 1];
			currentIndex++;
			ret.typ = leqsym;
		}
		else
		{
			ret.typ = lessym;
		}
		break;
	case '>':
		if (expression[currentIndex + 1] == '=')
		{
			ret.text += expression[currentIndex + 1];
			currentIndex++;
			ret.typ = geqsym;
		}
		else
		{
			ret.typ = gtrsym;
		}
		break;
	case '+':
		ret.typ = plussym;
		break;
	case '-':
		ret.typ = minussym;
		break;
	case '*':
		ret.typ = multsym;
		break;
	case '/':
		ret.typ = divsym;
		break;
	case '^':
		ret.typ = powsym;
		break;
	default:
		throw EquationException("Unexpected character", currentIndex);
	}

	currentIndex++;

	return ret;
}


bool Lexer::isDone(){
	return done;
}

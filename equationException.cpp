#include "equationException.h"

EquationException::EquationException(std::string msg, int index)
{

	message = msg;
	this->index = index;
}

std::string EquationException::what()
{
	string ret = message + " at line " + to_string(index);
	
	return string(ret);

}
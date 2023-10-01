#include "equationException.h"

EquationException::EquationException(std::string msg, int index)
{

	message = msg;
	this->index = index;
}

std::string EquationException::what()
{
	std::string ret = message + " at index " + std::to_string(index);
	
	return std::string(ret);

}
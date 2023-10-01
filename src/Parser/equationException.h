#ifndef _EQUATIONEXCEPTION_H
#define _EQUATIONEXCEPTION_H

#include <iostream>
#include <string>


class EquationException : public std::exception
{
private:
	std::string message;
	int index;

public:

	EquationException(std::string msg, int index);
	std::string what();
};

#endif
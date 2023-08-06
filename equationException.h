#ifndef _EQUATIONEXCEPTION_H
#define _EQUATIONEXCEPTION_H

#include <iostream>

using namespace std;

class EquationException : public exception
{
private:
	string message;
	int index;

public:

	EquationException(string msg, int index);
	string what();
};

#endif
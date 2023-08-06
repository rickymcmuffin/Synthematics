#include <iostream>
#include "equationException.h"

int main(){

	try{
		throw EquationException("bruh", 4);
	} catch (EquationException e){
		std::cout << e.what();
	}
	return 0;
}
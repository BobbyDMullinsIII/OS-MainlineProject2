#pragma once

#include <string>
#include "StaticMethods.h"


class StaticMethods
{
public:
	static bool IsPowerOfTwo(int x);
	static std::string removeNonLetters(std::string s);

private:
	//Constructors private because C++ does not have static classes
	//This is a way to make a "static" class in C++ that is similar to C# and Java
	StaticMethods();
	~StaticMethods();

};

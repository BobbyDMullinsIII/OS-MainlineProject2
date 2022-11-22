#include <string>
#include "Message.h"

//Constructor
Message::Message()
{
	this->ivalue = -1;
	this->dvalue = -1;
	memset(&this->cvalue[0], 0, sizeof(this->cvalue)); //Sets all characters in cvalue char array to 0 initially
}

//Parameterized Constructor
Message::Message(int i, double d, char c[56])
{
	this->ivalue = i;
	this->dvalue = d;
	strcpy_s(cvalue, c); //Copies c into cvalue
}


//Deconstructor
Message::~Message() {}
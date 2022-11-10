#include <iostream>
#include <fstream>
#include <string>
#include "User.h"
using namespace std;

//Paramaterized Constructor
User::User(string userName, int userID)
{
	this->name = userName;
	this->ID = userID;
}


//Deconstructor
User::~User() {}
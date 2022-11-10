#pragma once

#include <string>
#include "User.h"

class User
{
public:
    User(string userName, int userID);
    ~User();

    string name;
    int ID;

private:

};

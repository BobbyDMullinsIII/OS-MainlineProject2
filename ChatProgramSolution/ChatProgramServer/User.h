#pragma once

#include <string>
#include "User.h"

class User
{
public:
    User(std::string userName, int userID);
    ~User();

    std::string name;
    int ID;

private:

};

#pragma once

#include <string>
#include "Message.h"

class Message
{
public:
    Message();
    Message(int i, double d, char c[56]);
    ~Message();

    int    ivalue;
    double dvalue;
    char   cvalue[56];

private:

};


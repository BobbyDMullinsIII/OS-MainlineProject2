#pragma once

//Includes taken from example client.cc file (And Windows equivalents)
#include <stdlib.h>
#include <io.h>
#include <Winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string.h>

//Normal includes
#include <string>
#include <qmessagebox.h>
#include "Message.h"
#include "User.h"
#include "Client.h"

class Client
{
public:
    Client();
    ~Client();

    char hostname[81];
    struct addrinfo* myinfo;
    int sockdesc;
    char portnum[81];
    Message mymessage;
    int connection;
    int value;

private:

};

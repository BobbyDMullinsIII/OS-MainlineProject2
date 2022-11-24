#pragma once

#include <string>
#include "User.h"
#include "Client.h"
#include "ClientController.h"

class ClientController
{
public:
    ClientController();
    ~ClientController();

    void RunClientProgram();
    Client InitializeClient();


private:
};


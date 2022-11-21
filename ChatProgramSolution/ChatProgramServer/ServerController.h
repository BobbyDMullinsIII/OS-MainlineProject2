#pragma once

#include <string>
#include "Message.h"
#include "Server.h"
#include "ServerController.h"

class ServerController
{
public:
    ServerController();
    ~ServerController();

    void RunServerProgram();
    Server InitializeServer();


private:
};


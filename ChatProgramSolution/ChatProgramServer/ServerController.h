#pragma once

#include <string>
#include "Message.h"
#include "Server.h"
#include "ChatProgramServer.h"
#include "ServerController.h"

class ServerController
{
public:
    ServerController();
    ~ServerController();

    ChatProgramServer swindow; //Main GUI of server program (Using Qt)

    void RunServerProgram();
    Server InitializeServer();


private:
};


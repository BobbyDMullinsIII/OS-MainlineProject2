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

    void RunServerProgram(std::string port);
    static void RunServerLoop(std::string port);
    static void HandleClient(int connection);


private:
};


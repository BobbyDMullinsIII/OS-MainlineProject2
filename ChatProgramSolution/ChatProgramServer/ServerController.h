#pragma once

#include <string>
#include <vector>
#include "Server.h"
#include "ServerController.h"

class ServerController
{
public:
    ServerController();
    ServerController(const ServerController& s);
    ~ServerController();

    Server server;

    void RunServerLoop(std::string port);

private:
};
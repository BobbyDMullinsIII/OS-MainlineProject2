#pragma once

#include <string>
#include <vector>
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


signals:
    void modifyIncomingTextObject(std::string newString);
    void modifySentTextObject(std::string newString);


private:
};


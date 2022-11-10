#pragma once

#include <string>
#include "User.h"
#include "Client.h"
#include "Server.h"
#include "ChatProgramProject.h"
#include "ProgramController.h"

class ProgramController
{
public:
    ProgramController();
    ~ProgramController();

    ChatProgramProject window;

    void RunProgram();
    Server InitializeServer();
    Client InitializeClient();


private:
};


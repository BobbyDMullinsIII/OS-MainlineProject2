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

    void RunProgram();
    Server InitializeServer();
    Client InitializeClient();


private:
};


#pragma once

#include <string>
#include "Message.h"
#include "User.h"
#include "Client.h"
#include "Server.h"
#include "StaticMethods.h"
#include "ChatProgramProject.h"
#include "ProgramController.h"

class ProgramController
{
public:
    ProgramController();
    ~ProgramController();

    ChatProgramProject window; //Main GUI of client chat program (Using Qt)

    void RunProgram();
    Server InitializeServer();
    Client InitializeClient();


private:
};


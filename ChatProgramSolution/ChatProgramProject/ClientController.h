#pragma once

#include <string>
#include "Message.h"
#include "User.h"
#include "Client.h"
#include "ChatProgramProject.h"
#include "ClientController.h"

class ClientController
{
public:
    ClientController();
    ~ClientController();

    ChatProgramProject cwindow; //Main GUI of client chat program (Using Qt)

    void RunClientProgram();
    Client InitializeClient();


private:
};


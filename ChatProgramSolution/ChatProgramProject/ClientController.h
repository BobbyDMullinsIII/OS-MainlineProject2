#pragma once

#include <string>
#include "User.h"
#include "Client.h"
#include "ClientController.h"

class ClientController
{
public:
    ClientController();
    ClientController(const ClientController& c);
    ~ClientController();

    Client client;

    void RunClientLoop(std::string port, std::string hostname, std::string username);
    void sendMessage(std::string messageText);

private:
};


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

    //Struct for storing message values
    //1782 + 10 + 256 = 2048
    struct message {
        char   cvalue[1782]; //Actual message contents
        char   type[10];    //Type of message ('CLIENT' = client will have updated list, 'NORMAL' = normal message to send between clients and server, 'DISCON' = user disconnect)
        char   name[256];   //Name of thing and/or person that sent message
    };

    Client client;

    void RunClientLoop(std::string port, std::string hostname, std::string username);
    void sendMessage(std::string messageText);
    message createNewMessage(std::string content, std::string type, std::string name);
    std::string createUIMessage(std::string content, std::string name);

private:
};


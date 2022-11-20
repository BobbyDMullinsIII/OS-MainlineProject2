#pragma once

//Includes taken from example server.cc file (And Windows equivalents)
#include <stdlib.h>
#include <io.h>
#include <Winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string.h>

//Normal includes
#include <string>
#include <qmessagebox.h>
#include "Message.h"
#include "Server.h"

class Server
{
public:
	Server();
	~Server();

	struct addrinfo* myinfo;
	int sockdesc;
	char portnum[81];
	Message mymessage;
	int connection;
	int value;

	void createPortNum(std::string port);
	void createSockDesc();
	void createAddressRecord();
	void bindSocket();
	void listenSocket();

private:

};

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
#include <QObject>
#include <QVariant>
#include "CopyableQObject.h"
#include "User.h"
#include "Server.h"

class Server : public CopyableQObject
{
	Q_OBJECT
public:
	Server();
	~Server();

	struct addrinfo* myinfo;
	int sockdesc;
	char portnum[81];
	int connection;

	void InitializeServer(std::string port);
	void createPortNum(std::string port);
	void createSockDesc();
	void createAddressRecord();
	void bindSocket();
	void listenSocket();
	void HandleClient(int connection);
	message GetMsg();
	void PutMsg(message messa);


	void sendIncomeMessageUI(std::string imessage);
	void sendSentMessageUI(std::string smessage);
	void sendError(bool doExit, std::string title, std::string text);
	void sendInfo(std::string title, std::string text);

	Q_SIGNAL void appendIncomeMessageSignal(std::string incomeMessage);
	Q_SIGNAL void appendSentMessageSignal(std::string sentMessage);
	Q_SIGNAL void sendErrorMessage(bool exit, std::string title, std::string text);
	Q_SIGNAL void sendInfoMessage(std::string title, std::string text);

private:

};

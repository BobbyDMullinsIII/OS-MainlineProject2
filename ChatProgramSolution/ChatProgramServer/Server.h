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

	//Struct for storing message values
	//1782 + 10 + 256 = 2048
	struct message {
		char   cvalue[1782]; //Actual message contents
		char   type[10]; //Type of message ('CLIENT' = client will have updated list, 'NORMAL' = normal message to send between clients and server, 'DISCON' = user disconnect)
		char   name[256];   //Name of thing and/or person that sent message
	};

	//Struct for storing user and their corresponding connection in one spot
	struct userConnect {
		int connection;
		std::string userName;
	};

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
	message createNewMessage(std::string content, std::string type, std::string name);
	std::string createUIMessage(std::string content, std::string name);
	void updateClientList();
	void removeConnectionFromVector(int currentConnection);
	void sendToOtherClients(int currentConnections, message messageToSend);
	message GetMsg();
	void PutMsg(message messa);

	void sendNewClientListUI(std::string newList);
	void sendIncomeMessageUI(std::string imessage);
	void sendSentMessageUI(std::string smessage);
	void sendError(bool doExit, std::string title, std::string text);
	void sendInfo(std::string title, std::string text);

	Q_SIGNAL void sendNewClientListSignal(std::string newList);
	Q_SIGNAL void appendIncomeMessageSignal(std::string incomeMessage);
	Q_SIGNAL void appendSentMessageSignal(std::string sentMessage);
	Q_SIGNAL void sendErrorMessage(bool exit, std::string title, std::string text);
	Q_SIGNAL void sendInfoMessage(std::string title, std::string text);

private:

};

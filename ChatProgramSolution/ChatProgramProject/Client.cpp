//Date library taken from GitHub
#include "date.h"

//Includes taken from example client.cc file (And Windows equivalents)
#include <stdlib.h>
#include <io.h>
#include <Winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string.h>

//Normal includes
#include <string>
#include "User.h"
#include "Client.h"

struct message {
	char   cvalue[102]; //Actual message contents
	char   type[10]; //Type of message ('CLIENT' = client will have updated list, 'NORMAL' = normal message to send between clients and server)
	char   name[16];   //Name of thing and/or person that sent message
};

//Parameterized Constructor
Client::Client()
{
    
}

//Deconstructor
Client::~Client() {}

//Method for initializing client
void Client::InitializeClient(std::string port, std::string hostname)
{
	createHostName(hostname);
	createPortNum(port);
	createSockDesc();
	createAddressRecord();
	connectToHost();
}

//Method for creating hostname for the client
void Client::createHostName(std::string host)
{
	strcpy_s(this->hostname, host.c_str());
}

//Method for creating port number for the client
void Client::createPortNum(std::string port)
{
	//If input port is -1, set portnumber to standard 2000
	if (port == "-1")
	{
		strcpy_s(this->portnum, "2000");
	}
	else
	{
		strcpy_s(this->portnum, port.c_str());
	}
}

//Method for creating socket for the client
void Client::createSockDesc()
{
	//Creates socket descriptor
	//AF_INET = Binding to IP address(Should probably use this one)
	//AF_UNIX = Unix pathnames and directly for sockets
	//SOCK_STREAM = TCP (Should probably use this one)
	//SOCK_DGRAM = UDP
	this->sockdesc = socket(AF_INET, SOCK_STREAM, 0);

	//Shows messagebox with message if error occurred creating client socket
	if (this->sockdesc < 0)
	{
		int wsaError = WSAGetLastError(); //Gets last error if there was an error creating socket

		//String to put into messagebox
		std::string message = "There was an error creating the socket in the client.\nsockdesc: ";
		message += std::to_string(this->sockdesc);
		message += "\nWSA Error: ";
		message += std::to_string(wsaError);

		sendError(true, "Client Socket Error", message); //Send error
	}
}

//Method for creating address record for the client
void Client::createAddressRecord()
{
	int returnVal = getaddrinfo(this->hostname, this->portnum, NULL, &this->myinfo);

	//Shows messagebox with message if error occurred getting the address info for the client
	if (returnVal != 0)
	{
		//String to put into messagebox
		//Link for error codes: https://learn.microsoft.com/en-us/windows/win32/winsock/windows-sockets-error-codes-2
		std::string message = "There was an error getting the address in the client.\nreturnVal: ";
		message += std::to_string(returnVal);

		sendError(true, "Client Address Error", message); //Send error
	}
}

//Method for connecting to the host from the client
void Client::connectToHost()
{
	this->connection = ::connect(this->sockdesc, this->myinfo->ai_addr, this->myinfo->ai_addrlen);

	//Shows messagebox with message if error occurred connecting to the host
	if (this->connection < 0)
	{
		//String to put into messagebox
		std::string message = "There was an error connecting to the host from the client.\nconnection: ";
		message += std::to_string(this->connection);

		sendError(true, "Client Host Connection Error", message); //Send error
	}
	else //Shows client host connection if successful
	{
		//String to put into messagebox
		std::string message = "Connection successful.\nClient connection: ";
		message += std::to_string(this->connection);

		//sendInfo("Client Host Connection Information", message); //Send message to main GUI to be displayed in a message box
	}
}

//Method for sending new client list to main ui
void Client::sendNewClientListUI(std::string newList)
{
	emit sendNewClientListSignal(newList);
}

//Method for sending outgoing(sent) message to main ui
void Client::sendSentMessageUI(std::string smessage)
{
	emit appendSentMessageSignal(smessage); //Sends to main ui
}

//Method for sending incoming message to main ui
void Client::sendIncomeMessageUI(std::string imessage)
{
	emit appendIncomeMessageSignal(imessage); //Sends to main ui
}

//Method for sending error message to main ui to show message
void Client::sendError(bool doExit, std::string title, std::string text)
{
	emit sendErrorMessage(doExit, title, text); //Emit error message to main window
}

//Method for sending error message to main ui to show message
void Client::sendInfo(std::string title, std::string text)
{
	emit sendInfoMessage(title, text); //Emit error message to main window
}
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

//Parameterized Constructor
Server::Server()
{
	
}

//Deconstructor
Server::~Server() {}

//Method for creating socket for the server
void Server::createSockDesc()
{
	//Creates socket descriptor
	this->sockdesc = socket(AF_INET, SOCK_STREAM, 0);

	//Shows messagebox with message if error occurred creating server socket
	if (sockdesc < 0)
	{
		QMessageBox messageBox;
		messageBox.critical(0, "Server Socket Error", "There was an error creating the socket in the server.");
		messageBox.setFixedSize(640, 480);
	}
}

//Method for creating port number for the server
void Server::createPortNum(std::string port)
{
	//If input port is 0, set portnumber to standard 2000
	if (port == "0")
	{
		strcpy_s(this->portnum, "2000");
	}
	else
	{
		strcpy_s(this->portnum, port.c_str());
	}
}

//Method for creating address record for the server
void Server::createAddressRecord()
{
	//Shows messagebox with message if error occurred getting the address for the server
	if (getaddrinfo("127.0.0.1", this->portnum, NULL, &this->myinfo) != 0)
	{
		QMessageBox messageBox;
		messageBox.critical(0, "Server Address Error", "There was an error getting the address in the server.");
		messageBox.setFixedSize(640, 480);
	}
}

void Server::bindSocket()
{
	//Shows messagebox with message if error occurred binding the socket for the server
	if (bind(this->sockdesc, this->myinfo->ai_addr, this->myinfo->ai_addrlen) < 0)
	{
		QMessageBox messageBox;
		messageBox.critical(0, "Server Binding Error", "There was an error binding the socket to an address in the server.");
		messageBox.setFixedSize(640, 480);
	}
}

void Server::listenSocket()
{
	//Shows messagebox with message if error occurred in the listen for the server
	if (listen(this->sockdesc, 1) < 0)
	{
		QMessageBox messageBox;
		messageBox.critical(0, "Server Listen Error", "There was an error in listen in the server.");
		messageBox.setFixedSize(640, 480);
	}
}
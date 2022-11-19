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

//Method for creating port number for the server
void Server::createPortNum(std::string port)
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

//Method for creating socket for the server
void Server::createSockDesc()
{
	//Creates socket descriptor
	//AF_INET = Binding to IP address(Should probably use this one)
	//AF_UNIX = Unix pathnames and directly for sockets
	//SOCK_STREAM = TCP (Should probably use this one)
	//SOCK_DGRAM = UDP
	this->sockdesc = socket(AF_INET, SOCK_STREAM, 0);

	//Shows messagebox with message if error occurred creating server socket
	if (this->sockdesc < 0)
	{
		//String to put into messagebox
		std::string message = "There was an error creating the socket in the server.\nsockdesc: ";
		message += std::to_string(this->sockdesc);

		QMessageBox messageBox;
		messageBox.critical(0, "Server Socket Error", message.c_str());
		messageBox.setFixedSize(640, 480);
	}
}

//Method for creating address record for the server
void Server::createAddressRecord()
{
	int returnVal = getaddrinfo("127.0.0.1", this->portnum, NULL, &this->myinfo);

	//Shows messagebox with message if error occurred getting the address for the server
	if (returnVal != 0)
	{
		//String to put into messagebox
		//Link for error codes: https://learn.microsoft.com/en-us/windows/win32/winsock/windows-sockets-error-codes-2
		std::string message = "There was an error getting the address in the server.\nreturnVal: ";
		message += std::to_string(returnVal);

		QMessageBox messageBox;
		messageBox.critical(0, "Server Address Error", message.c_str());
		messageBox.setFixedSize(640, 480);
	}
}

//Method for binding socket on the server
void Server::bindSocket()
{
	int returnVal = bind(this->sockdesc, this->myinfo->ai_addr, this->myinfo->ai_addrlen);

	//Shows messagebox with message if error occurred binding the socket for the server
	if (returnVal < 0)
	{
		//String to put into messagebox
		std::string message = "There was an error binding the socket to an address in the server.\nreturnVal: ";
		message += std::to_string(returnVal);

		QMessageBox messageBox;
		messageBox.critical(0, "Server Binding Error", message.c_str());
		messageBox.setFixedSize(640, 480);
	}
}

//Method for listening to socket on the server
void Server::listenSocket()
{
	int returnVal = listen(this->sockdesc, 1);

	//Shows messagebox with message if error occurred in the listen for the server
	if (returnVal < 0)
	{
		//String to put into messagebox
		std::string message = "There was an error in listen in the server.\nreturnVal: ";
		message += std::to_string(returnVal);

		QMessageBox messageBox;
		messageBox.critical(0, "Server Listen Error", message.c_str());
		messageBox.setFixedSize(640, 480);
	}
}
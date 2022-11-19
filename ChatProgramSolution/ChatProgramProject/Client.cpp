//Includes taken from example client.cc file (And Windows equivalents)
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
#include "User.h"
#include "Client.h"

//Parameterized Constructor
Client::Client()
{
    
}

//Deconstructor
Client::~Client() {}

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
		//String to put into messagebox
		std::string message = "There was an error creating the socket in the client.\nsockdesc: ";
		message += std::to_string(this->sockdesc);

		QMessageBox messageBox;
		messageBox.critical(0, "Client Socket Error", message.c_str());
		messageBox.setFixedSize(640, 480);
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

		QMessageBox messageBox;
		messageBox.critical(0, "Client Address Error", message.c_str());
		messageBox.setFixedSize(640, 480);
	}
}

//Method for connecting to the host from the client
void Client::connectToHost()
{
	this->connection = connect(this->sockdesc, this->myinfo->ai_addr, this->myinfo->ai_addrlen);

	//Shows messagebox with message if error occurred connecting to the host
	if (this->connection < 0)
	{
		//String to put into messagebox
		std::string message = "There was an error connecting to the host from the client.\nconnection: ";
		message += std::to_string(this->connection);

		QMessageBox messageBox;
		messageBox.critical(0, "Client Host Connection Error", message.c_str());
		messageBox.setFixedSize(640, 480);
	}
	else //Shows client host connection if successful
	{
		//String to put into messagebox
		std::string message = "Connection successful.\nClient connection: ";
		message += std::to_string(this->connection);

		QMessageBox messageBox;
		messageBox.information(0, "Client Host Connection Information", message.c_str());
		messageBox.setFixedSize(640, 480);
	}
}
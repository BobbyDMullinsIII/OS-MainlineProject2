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
	if (sockdesc < 0)
	{
		QMessageBox messageBox;
		messageBox.critical(0, "Client Socket Error", "There was an error creating the socket in the client.");
		messageBox.setFixedSize(640, 480);
	}
}

//Method for creating address record for the client
void Client::createAddressRecord()
{
	//Shows messagebox with message if error occurred getting the address for the client
	if (getaddrinfo(this->hostname, this->portnum, NULL, &this->myinfo) != 0)
	{
		QMessageBox messageBox;
		messageBox.critical(0, "Client Address Error", "There was an error getting the address in the client.");
		messageBox.setFixedSize(640, 480);
	}
}

//Method for connecting to the host from the client
void Client::connectToHost()
{
	//Shows messagebox with message if error occurred connecting to the host
	this->connection = connect(this->sockdesc, this->myinfo->ai_addr, this->myinfo->ai_addrlen);
	if (this->connection < 0)
	{
		QMessageBox messageBox;
		messageBox.critical(0, "Client Host Connection Error", "There was an error connecting to the host from the client.");
		messageBox.setFixedSize(640, 480);
	}
	else //Shows client host connection if successful
	{
		QMessageBox messageBox;
		messageBox.information(0, "Client Host Connection Information", "Client connection = %d", this->connection);
		messageBox.setFixedSize(640, 480);
	}
}
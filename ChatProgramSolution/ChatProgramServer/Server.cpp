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
#include "date.h"
#include "Server.h"

struct message {
	int    ivalue;
	double dvalue;
	char   cvalue[56];
};

//Constructor
Server::Server()
{

}

//Deconstructor
Server::~Server() {}

//Method for initializing server
void Server::InitializeServer(std::string port)
{
	createPortNum(port);
	createSockDesc();
	createAddressRecord();
	bindSocket();
	listenSocket();
}

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
		int wsaError = WSAGetLastError(); //Gets last error if there was an error creating socket

		//String to put into messagebox
		std::string message = "There was an error creating the socket in the server.\nsockdesc: ";
		message += std::to_string(this->sockdesc);
		message += "\nWSA Error: ";
		message += std::to_string(wsaError);

		sendError(true, "Server Socket Error", message); //Send error
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

		sendError(true, "Server Address Error", message); //Send error
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

		sendError(true, "Server Binding Error", message); //Send error
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

		sendError(true, "Server Listen Error", message); //Send error
	}
}

//Method for handling a client connection
void Server::HandleClient(int connection)
{
	int currentConnection = connection;
	int messageVal;
	int userID;			      //Current ID of user
	std::string userName;     //Variable for keeping username
	message incomeMessage;    //Variable for incoming messages from client
	std::string inMsgToPrint;
	message sentMessage;      //Variable for sent messages to client
	std::string outMsgToPrint;

	//The first message from client is their username
	//messageVal = recv(currentConnection, (char*)&incomeMessage, sizeof(message), 0);
	//userName = incomeMessage.cvalue;

	//Infinite loop to keep reading and writing messages
	for (;;)
	{
		//Reads a message from client
		messageVal = recv(currentConnection, (char*)&incomeMessage, sizeof(message), 0);

		//If user types only "DISCONNECT" (all caps) as their message, they disconnect
		if (incomeMessage.cvalue == "DISCONNECT")
		{
			closesocket(currentConnection);

			break;
		}
		else
		{
			//Prints incoming message out on GUI
			inMsgToPrint = ""; //Set to empty for new message
			inMsgToPrint.append(date::format("%F %T", std::chrono::system_clock::now()) + "\n"); //Appends date and exact time and new line
			inMsgToPrint.append(userName + "\n"); //Appends username and new line
			inMsgToPrint.append(incomeMessage.cvalue); //Appends actual message
			inMsgToPrint.append("\n"); //Appends another new line
			emit appendIncomeMessageSignal(inMsgToPrint); //Sends inMsgToPrint to main ui

			//Increments message variables and prepares message for sending back to client
			sentMessage.ivalue = incomeMessage.ivalue + 1;
			sentMessage.dvalue = incomeMessage.dvalue + 1.0;
			strcpy_s(sentMessage.cvalue, "Server: Message received");

			//Prints outgoing message out on GUI
			outMsgToPrint = ""; //Set to empty for new message
			outMsgToPrint.append(date::format("%F %T", std::chrono::system_clock::now()) + "\n"); //Appends date and exact time and new line
			outMsgToPrint.append("Server\n"); //Appends username and new line
			outMsgToPrint.append(sentMessage.cvalue); //Appends actual message
			outMsgToPrint.append("\n"); //Appends another new line
			emit appendSentMessageSignal(outMsgToPrint); //Sends outMsgToPrint to main ui

			//Sends message back to client
			send(currentConnection, (char*)&sentMessage, sizeof(message), 0);
		}
	}
}

//Method for sending error message to main ui to show message
void Server::sendError(bool doExit, std::string title, std::string text)
{
	emit sendErrorMessage(doExit, title, text); //Emit error message to main window
}
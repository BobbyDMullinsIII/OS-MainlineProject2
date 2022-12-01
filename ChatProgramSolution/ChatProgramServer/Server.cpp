//Date library taken from GitHub https://github.com/HowardHinnant/date/blob/master/include/date/date.h
#include "date.h"

//Includes taken from example server.cc file (And Windows equivalents)
#include <stdlib.h>
#include <io.h>
#include <Winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string.h>

//Normal includes
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <queue>
#include "Server.h"

std::queue<Server::message> msgs;
std::mutex m;
std::condition_variable ConVar;
std::vector<Server::userConnect> connectVector;

//Constructor
Server::Server()
{
	this->myinfo = NULL;
	this->sockdesc = NULL;
	this->portnum[81] = NULL;
	this->connection = NULL;
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
	std::string userName = "Placeholder Username";     //Variable for keeping username
	Server::message incomeMessage;    //Variable for incoming messages from client
	std::string inMsgToPrint;
	Server::message sentMessage;      //Variable for sent messages to client
	std::string outMsgToPrint;

	//The first message from client is their username
	messageVal = recv(currentConnection, (char*)&incomeMessage, sizeof(Server::message), 0);
	userName = incomeMessage.cvalue;

	//Adds username and corresponding connection value to the vector
	Server::userConnect vectorValue;
	vectorValue.connection = currentConnection;
	vectorValue.userName = userName;
	connectVector.push_back(vectorValue);

	//Notifies all other clients that a new client has connected
	std::string messageContent = userName + " has connected";
	sentMessage = createNewMessage(messageContent, "NORMAL", "Server");
	send(currentConnection, (char*)&sentMessage, sizeof(Server::message), 0);
	sendToOtherClients(currentConnection, sentMessage);

	//Prints outgoing message out on GUI
	outMsgToPrint = createUIMessage(sentMessage.cvalue, "Server");
	sendSentMessageUI(outMsgToPrint); //Sends outMsgToPrint to main ui

	updateClientList(); //Sends updated client list to all clients and server ui

	//Infinite loop to keep reading and writing messages
	for (;;)
	{
		//Reads a message from client
		messageVal = recv(currentConnection, (char*)&incomeMessage, sizeof(Server::message), 0);

		//If user types only "DISCONNECT" (all caps) as their message, they disconnect
		std::string strMessage(incomeMessage.cvalue);
		if (strMessage == "DISCONNECT")
		{
			//Prepares message for sending back to client for final time before disconnection
			std::string finalMessage = userName + " disconnected";
			sentMessage = createNewMessage(finalMessage, "DISCON", "Server");
			send(currentConnection, (char*)&sentMessage, sizeof(Server::message), 0);

			Server::message disconMessage = createNewMessage(finalMessage, "NORMAL", "Server"); //Create disconnect message for other users
			sendToOtherClients(currentConnection, disconMessage); //Sends disconnect message from server to the other clients to show that user disconnected

			//Prints outgoing message out on GUI
			outMsgToPrint = createUIMessage(disconMessage.cvalue, "Server");
			sendSentMessageUI(outMsgToPrint); //Sends outMsgToPrint to main ui

			removeConnectionFromVector(currentConnection); //Removes current user from connection/name vector
			updateClientList(); //Sends updated client list to all clients and server ui
			closesocket(currentConnection); //Close socket connection with disconnecting client
			break; //Break loop, ending this thread
			break;
			break;
		}
		else
		{
			//Sends normal message from one client to the other clients
			sendToOtherClients(currentConnection, incomeMessage);

			//Prints incoming message out on GUI
			inMsgToPrint = createUIMessage(incomeMessage.cvalue, incomeMessage.name);
			sendIncomeMessageUI(inMsgToPrint); //Sends inMsgToPrint to main ui

			//Prepares message for sending back to client and sends
			sentMessage = createNewMessage("Message received", "NORMAL", "Server");
			send(currentConnection, (char*)&sentMessage, sizeof(Server::message), 0);

			//Prints outgoing message out on GUI
			outMsgToPrint = createUIMessage(sentMessage.cvalue, "Server");
			sendSentMessageUI(outMsgToPrint); //Sends outMsgToPrint to main ui
		}
	}
}

//Method for creating a new message from 3 strings and returning it 
Server::message Server::createNewMessage(std::string content, std::string type, std::string name)
{
	Server::message newMessage;

	strcpy_s(newMessage.cvalue, content.c_str());
	strcpy_s(newMessage.type, type.c_str());
	strcpy_s(newMessage.name, name.c_str());

	return newMessage;
}

//Method for creating a message to put on the ui (in std::string form) and returning it
std::string Server::createUIMessage(std::string content, std::string name)
{
	//Prints outgoing message out on GUI
	std::string newUIMessage = ""; //Set to empty for new message

	newUIMessage.append("UTC " + date::format("%F %T", std::chrono::system_clock::now())); //Appends date and exact time
	newUIMessage = newUIMessage.substr(0, newUIMessage.find("."));
	newUIMessage.append("\n"); //Appends another new line
	newUIMessage.append(name); //Appends username of message sender
	newUIMessage.append("\n"); //Appends another new line
	newUIMessage.append(content); //Appends actual message

	return newUIMessage;
}

//Method for sending normal messages from one client to other clients
void Server::sendToOtherClients(int currentConnection, Server::message messageToSend)
{
	for (int i = 0; i < connectVector.size(); i++)
	{
		if (connectVector[i].connection != currentConnection)
		{
			send(connectVector[i].connection, (char*)&messageToSend, sizeof(Server::message), 0);
		}
	}
}

//Method for removing a connection from the vector, along with its corresponding username
void Server::removeConnectionFromVector(int currentConnection)
{
	for (int i = 0; i < connectVector.size(); i++)
	{
		if (connectVector[i].connection == currentConnection)
		{
			connectVector.erase(connectVector.begin() + i);
		}
	}
}

//Method for sending updated client list to clients and server ui
void Server::updateClientList()
{
	std::string clientList = "";
	for (int i = 0; i < connectVector.size(); i++)
	{
		clientList.append(connectVector[i].userName);
		clientList.append("\n\n");
	}

	sendNewClientListUI(clientList); //Send updated client list to server ui

	//Send updated client list to all clients
	Server::message newListMessage = createNewMessage(clientList, "CLIENT", "Server");

	for (int i = 0; i < connectVector.size(); i++)
	{
		send(connectVector[i].connection, (char*)&newListMessage, sizeof(Server::message), 0);

	}
}


Server::message Server::GetMsg()
{
	Server::message messa;
	std::unique_lock<std::mutex> lock(m);

	//may need to check for multiple messages
	ConVar.wait(lock, []() {return not msgs.empty(); });
	//gets client message
	//messa = msgs.front();
	//removes message from queue
	msgs.pop();

	return messa;
}

void Server::PutMsg(Server::message messa)
{
	std::lock_guard<std::mutex> lk(m);
	//enqueue message
	//msgs.push(messa);
	//notifies conditional variable, and allows a waiting thread to run
	ConVar.notify_one();
}

//Method for sending new client list to main ui
void Server::sendNewClientListUI(std::string newList)
{
	emit sendNewClientListSignal(newList); //Sends new list to main ui
}

//Method for sending incoming message to main ui
void Server::sendIncomeMessageUI(std::string imessage)
{
	emit appendIncomeMessageSignal(imessage); //Sends to main ui
}

//Method for sending outgoing(sent) message to main ui
void Server::sendSentMessageUI(std::string smessage)
{
	emit appendSentMessageSignal(smessage); //Sends to main ui
}

//Method for sending error message to main ui to show message
void Server::sendError(bool doExit, std::string title, std::string text)
{
	emit sendErrorMessage(doExit, title, text); //Emit error message to main window
}

//Method for sending information message to main ui to show message
void Server::sendInfo(std::string title, std::string text)
{
	emit sendInfoMessage(title, text); //Emit information message to main window
}
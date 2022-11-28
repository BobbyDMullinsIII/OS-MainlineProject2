//Date library taken from GitHub
#include "date.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "User.h"
#include "Client.h"
#include "ClientController.h"
using namespace std;

struct message {
	char   cvalue[102]; //Actual message contents
	char   type[10];    //Type of message ('CLIENT' = client will have updated list, 'NORMAL' = normal message to send between clients and server)
	char   name[16];   //Name of thing and/or person that sent message
};

//Constructor
ClientController::ClientController()
{
	this->client = Client();
}

//Copy Constructor
ClientController::ClientController(const ClientController& s)
{

}

//Deconstructor
ClientController::~ClientController() {}

//Method for running overall program
void ClientController::RunClientLoop(std::string port, std::string hostname, std::string username)
{
    //Variables and section of code is needed for Windows Sockets
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;

    wVersionRequested = MAKEWORD(2, 2);
    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0)
    {
		//String to put into messagebox
		std::string message = "There was an error with WSAStartup in the client. \nError: ";
		message += std::to_string(err);

		this->client.sendError(false, "Client WSAStartup Error", message.c_str());
    }
	else
	{
		this->client.username = username; //Set client username
		this->client.InitializeClient(port, hostname); //Initialize client and connect to server
		
		//Create message and send username to server
		message nameMessage;
		strcpy_s(nameMessage.cvalue, username.c_str());
		strcpy_s(nameMessage.type, "NORMAL");
		strcpy_s(nameMessage.name, username.c_str());
		send(this->client.sockdesc, (char*)&nameMessage, sizeof(message), 0);

		message incomeMessage; //Variable for all future messages from server

		//Continuously listen for messages from the server
		for (;;)
		{
			recv(this->client.sockdesc, (char*)&incomeMessage, sizeof(message), 0);

			//If message from server is a client list update, update client list on ui
			//if (clientUpdate)
			//{
				//this->client.sendNewClientListUI(incomeMessage.cvalue);
			//}
			//else
			///{
				//Prints incoming message from server out on GUI
				string inMsgToPrint = ""; //Set to empty for new message
				inMsgToPrint.append("UTC " + date::format("%F %T", std::chrono::system_clock::now())); //Appends date and exact time
				inMsgToPrint = inMsgToPrint.substr(0, inMsgToPrint.find("."));
				inMsgToPrint.append("\n"); //Appends another new line
				inMsgToPrint.append(incomeMessage.name); //Appends username of message sender
				inMsgToPrint.append("\n"); //Appends another new line
				inMsgToPrint.append(incomeMessage.cvalue); //Appends actual message
				inMsgToPrint.append("\n"); //Appends another new line
				this->client.sendIncomeMessageUI(inMsgToPrint); //Sends inMsgToPrint to main ui
			//}
		}
	}
}

void ClientController::sendMessage(std::string messageText)
{
	//Create message variable and send message to server
	message regularMessage;
	strcpy_s(regularMessage.cvalue, messageText.c_str());
	strcpy_s(regularMessage.type, "NORMAL");
	strcpy_s(regularMessage.name, this->client.username.c_str());
	send(this->client.sockdesc, (char*)&regularMessage, sizeof(message), 0);

	//Prints outgoing message sent from client to the ui
	string outMsgToPrint = ""; //Set to empty for new message
	outMsgToPrint.append("UTC " + date::format("%F %T", std::chrono::system_clock::now())); //Appends date and exact time
	outMsgToPrint = outMsgToPrint.substr(0, outMsgToPrint.find("."));
	outMsgToPrint.append("\n"); //Appends another new line
	outMsgToPrint.append(regularMessage.name); //Appends username of message sender
	outMsgToPrint.append("\n"); //Appends another new line
	outMsgToPrint.append(regularMessage.cvalue); //Appends actual message
	outMsgToPrint.append("\n"); //Appends another new line
	this->client.sendSentMessageUI(outMsgToPrint); //Sends outMsgToPrint to main ui

}
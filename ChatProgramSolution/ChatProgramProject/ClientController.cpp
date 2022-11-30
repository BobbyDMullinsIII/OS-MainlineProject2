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
		ClientController::message nameMessage;
		nameMessage = createNewMessage(username, "NORMAL", username);
		send(this->client.sockdesc, (char*)&nameMessage, sizeof(ClientController::message), 0);

		ClientController::message incomeMessage; //Variable for all future messages from server

		//Continuously listen for messages from the server
		for (;;)
		{
			recv(this->client.sockdesc, (char*)&incomeMessage, sizeof(ClientController::message), 0);

			//If message from server is a client list update, update client list on ui
			string type(incomeMessage.type);
			if (type == "CLIENT")
			{
				this->client.sendNewClientListUI(incomeMessage.cvalue);
			}
			else if (type == "NORMAL" || type == "DISCON")
			{
				//Prints incoming message from server out on GUI
				string inMsgToPrint = createUIMessage(incomeMessage.cvalue, incomeMessage.name);
				this->client.sendIncomeMessageUI(inMsgToPrint); //Sends inMsgToPrint to main ui

				//If string returned is a disconnect confirmation message, close socket and break loop
				if (type == "DISCON")
				{
					closesocket(this->client.sockdesc);
					this->client.sendNewClientListUI(""); //Empties client list on UI after disconnecting

					//Reset values for client object when finished
					this->client.hostname[81] = NULL;
					this->client.myinfo = NULL;
					this->client.sockdesc = NULL;
					this->client.portnum[81] = NULL;
					this->client.connection = NULL;
					this->client.value = NULL;
					this->client.username = "";

					break; //Break out of loop and thread
				}
			}
		}
	}
}

void ClientController::sendMessage(std::string messageText)
{
	//Create message variable and send message to server
	ClientController::message regularMessage;
	regularMessage = createNewMessage(messageText, "NORMAL",this->client.username);
	send(this->client.sockdesc, (char*)&regularMessage, sizeof(ClientController::message), 0);

	//Prints outgoing message sent from client to the ui
	string outMsgToPrint = createUIMessage(regularMessage.cvalue, regularMessage.name);
	this->client.sendSentMessageUI(outMsgToPrint); //Sends outMsgToPrint to main ui
}

//Method for creating a new message from 3 strings and returning it 
ClientController::message ClientController::createNewMessage(std::string content, std::string type, std::string name)
{
	ClientController::message newMessage;

	strcpy_s(newMessage.cvalue, content.c_str());
	strcpy_s(newMessage.type, type.c_str());
	strcpy_s(newMessage.name, name.c_str());

	return newMessage;
}

//Method for creating a message to put on the ui (in std::string form) and returning it
std::string ClientController::createUIMessage(std::string content, std::string name)
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
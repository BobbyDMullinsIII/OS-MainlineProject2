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
	int    ivalue;
	double dvalue;
	char   cvalue[56];
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
		//Code for client connect to server and send/receive loop goes here
		//(Does not need its own thread)
	}
}
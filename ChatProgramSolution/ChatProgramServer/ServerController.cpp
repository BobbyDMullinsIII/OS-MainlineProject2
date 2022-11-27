//Date library taken from GitHub
#include "date.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include "Server.h"
#include "ServerController.h"
using namespace std;

//Constructor
ServerController::ServerController()
{
	this->server = Server();
}

//Copy Constructor
ServerController::ServerController(const ServerController& s)
{

}

//Deconstructor
ServerController::~ServerController() {}

//Method for running server loop
void ServerController::RunServerLoop(string port)
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
		std::string message = "There was an error with WSAStartup in the server. \nError: ";
		message += std::to_string(err);

		this->server.sendError(false, "Server WSAStartup Error", message.c_str());
	}
	else
	{
		this->server.InitializeServer(port); //Initializes server

		//Infinite loop for receiving client connections
		for (;;)
		{
			//Loop will wait here until accept detects any new connections
			//Threads are needed because the GUI would not work because it would be stuck here without going on a different thread
			this->server.connection = accept(this->server.sockdesc, NULL, NULL);
			if (this->server.connection < 0)
			{
				this->server.sendError(false, "Accept Client Error", "There was an error accepting a client.");
			}
			else
			{
				//Will create new thread for each client that is accepted
				std::thread(&Server::HandleClient, this->server, this->server.connection).detach();
			}
		}
	}
}
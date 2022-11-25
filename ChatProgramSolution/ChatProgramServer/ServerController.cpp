#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include "date.h"
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
	 this->server.InitializeServer(port); //Initializes server

	//Infinite loop for receiving client connections
	for (;;)
	{
		//Loop will wait here until accept detects any new connections
		//Threads are needed because the GUI would not work because it would be stuck here without going on a different thread
		this->server.connection = accept(this->server.sockdesc, NULL, NULL);
		if (this->server.connection < 0)
		{
			QMessageBox messageBox;
			messageBox.critical(0, "Accept Client Error", "There was an error accepting a client.");
			messageBox.setFixedSize(640, 480);
		}
		else
		{
			//Will create new thread for each client that is accepted
			std::thread(&Server::HandleClient, this->server, this->server.connection).detach();
		}
	}
}
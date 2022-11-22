#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include "Message.h"
#include "Server.h"
#include "ServerController.h"
using namespace std;

//Constructor
ServerController::ServerController()
{

}


//Deconstructor
ServerController::~ServerController() {}

//Method for running overall server program using threads
void ServerController::RunServerProgram(string port)
{
	//Creates master thread for loop so program doesnt freeze during infinite loop
	//2 threads so far - 1 for program main execution, 1 for server loop
	thread loopThread(RunServerLoop, port);
}

//Method for running server loop
void ServerController::RunServerLoop(string port)
{
	Server server = Server(port); //Creates new server object and initializes it
	server.listenSocket(); //Server starts listening to the socket

	//Infinite loop for receiving client connections
	for (;;)
	{
		//Loop will wait here until accept detects any new connections
		//Threads are needed because the GUI would not work because it would be stuck here without going on a different thread
		server.connection = accept(server.sockdesc, NULL, NULL);
		if (server.connection < 0)
		{
			QMessageBox messageBox;
			messageBox.critical(0, "Accept Client Error", "There was an error accepting a client.");
			messageBox.setFixedSize(640, 480);
		}
		else
		{
			//Will create new thread for each client that is accepted (Not finished)
			new thread(HandleClient, server.connection);
		}
	}
}

//Method for handling a client connection
void ServerController::HandleClient(int connection)
{
	//Not finished
}
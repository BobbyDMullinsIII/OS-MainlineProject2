#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include "date.h"
#include "Server.h"
#include "ServerController.h"
using namespace std;

struct message {
	int    ivalue;
	double dvalue;
	char   cvalue[56];
};

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
			//Will create new thread for each client that is accepted
			new thread(&HandleClient, server.connection);
		}
	}
}

//Method for handling a client connection
void ServerController::HandleClient(int connection)
{
	int currentConnection = connection;
	int messageVal;
	int userID;			   //Current ID of user
	string userName;       //Variable for keeping username
	message incomeMessage; //Variable for incoming messages from client
	string inMsgToPrint;
	message sentMessage;   //Variable for sent messages to client
	string outMsgToPrint;

	//The first message from client is their username
	messageVal = recv(currentConnection, (char*)&incomeMessage, sizeof(message), 0);
    userName = incomeMessage.cvalue;



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
			inMsgToPrint = "";
			inMsgToPrint.append(date::format("%F %T", std::chrono::system_clock::now()) + "\n"); //Appends date and exact time and new line
			inMsgToPrint.append(userName + "\n"); //Appends username and new line
			inMsgToPrint.append(incomeMessage.cvalue); //Appends actual message
			//(NOT DONE)

			//Increments message variables and prepares message for sending back to client
			sentMessage.ivalue = incomeMessage.ivalue + 1;
			sentMessage.dvalue = incomeMessage.dvalue + 1.0;
			strcpy_s(sentMessage.cvalue, "Server: Message received");

			//Prints outgoing message out on GUI
			outMsgToPrint = "";
			outMsgToPrint.append(date::format("%F %T", std::chrono::system_clock::now()) + "\n"); //Appends date and exact time and new line
			outMsgToPrint.append("Server\n"); //Appends username and new line
			outMsgToPrint.append(sentMessage.cvalue); //Appends actual message
			//(NOT DONE)

			//Sends message back to client
			send(currentConnection, (char*)&sentMessage, sizeof(message), 0);
		}
	}
}
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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

//Method for running overall program
void ServerController::RunServerProgram()
{
	Server server = InitializeServer();
}

//Method for initializing server instance
Server ServerController::InitializeServer()
{
	Server newServer;

	//Code for initializing server goes here

	return newServer;
}
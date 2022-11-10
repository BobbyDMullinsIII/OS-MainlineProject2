#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "User.h"
#include "Client.h"
#include "Server.h"
#include "ChatProgramProject.h"
#include "ProgramController.h"
using namespace std;

//Constructor
ProgramController::ProgramController()
{

}


//Deconstructor
ProgramController::~ProgramController() {}

//Method for running overall program
void ProgramController::RunProgram()
{
	ChatProgramProject w;

	Server server = InitializeServer();
	Client client = InitializeClient(); //Will only have one client for now

	w.show();
}

//Method for initializing server instance
Server ProgramController::InitializeServer()
{
	Server newServer;

	//Code for initializing server goes here

	return newServer;
}

//Method for initializing client instance (There can be more than one)
Client ProgramController::InitializeClient()
{
	Client newClient;

	//Code for initializing client goes here

	return newClient;
}
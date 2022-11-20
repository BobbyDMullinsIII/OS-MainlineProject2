#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Message.h"
#include "User.h"
#include "Client.h"
#include "ChatProgramProject.h"
#include "ClientController.h"
using namespace std;

//Constructor
ClientController::ClientController()
{

}


//Deconstructor
ClientController::~ClientController() {}

//Method for running overall program
void ClientController::RunClientProgram()
{
	Client client = InitializeClient();

	cwindow.show(); //Show main GUI window of client chat program (Using Qt)
}

//Method for initializing client instance
Client ClientController::InitializeClient()
{
	Client newClient;

	//Code for initializing client goes here

	return newClient;
}
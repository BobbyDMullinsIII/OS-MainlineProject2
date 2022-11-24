#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "date.h"
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

}


//Deconstructor
ClientController::~ClientController() {}

//Method for running overall program
void ClientController::RunClientProgram()
{
	Client client = InitializeClient();
}

//Method for initializing client instance
Client ClientController::InitializeClient()
{
	Client newClient;

	//Code for initializing client goes here

	return newClient;
}
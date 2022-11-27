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
	 this->client = Client();

	 //Code for client connect to server and send/receive loop goes here
}
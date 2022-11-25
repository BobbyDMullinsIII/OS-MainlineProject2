#include <vector>
#include <thread>
#include "User.h"
#include "ChatProgramServer.h"
#include "InitServerDialog.h"
#include "ServerController.h"

ChatProgramServer::ChatProgramServer(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this); //Sets up this window for the server

    //Sets absolute objest names and background colors of text objects
    ui.sentTextObject->setObjectName("sentTextObject");
    ui.incomingTextObject->setObjectName("incomingTextObject");
    ui.clientTextObject->setObjectName("clientTextObject");

    //Set all strings to empty for now
    this->incomeString = "";       //Big string for appending all incoming messages to for display on ui (incomingTextObject)
    this->sentString = "";         //Big string for appending all incoming messages to for display on ui (sentTextObject)
    this->userDisplayString = "";  //Big string for displaying all currently connected clients on ui (clientTextObject)

    SControl = ServerController();

    QObject::connect(&SControl, SIGNAL(appendIncomeMessageSignal(std::string)), this, SLOT(appendIncomeMessage(std::string)));
    QObject::connect(&SControl, SIGNAL(appendSentMessageSignal(std::string)), this, SLOT(appendSentMessage(std::string)));
}

ChatProgramServer::~ChatProgramServer()
{}

void ChatProgramServer::AddUser(std::string userName, int userID)
{
    User newUser = User(userName, userID);
    this->userList.push_back(newUser);
}

void ChatProgramServer::RemoveUser(int userID)
{

}

//Method for running overall server program using threads
void ChatProgramServer::RunServerProgram(std::string port)
{
    //Creates master thread for loop so program doesnt freeze during infinite loop
    //2 threads so far - 1 for program main execution, 1 for server loop
    std::thread(&ServerController::RunServerLoop, &this->SControl, port).detach();
}

void ChatProgramServer::appendIncomeMessage(std::string incomeMessage)
{
    //Appends message to incomeString
    this->incomeString.append("\n\n" + incomeMessage);
    ui.incomingTextObject->append(QString::fromStdString("\n\n" + incomeMessage));
}

void ChatProgramServer::appendSentMessage(std::string sentMessage)
{
    //Appends message to sentString
    this->sentString.append("\n\n" + sentMessage);
    ui.sentTextObject->append(QString::fromStdString("\n\n" + sentMessage));
}

void ChatProgramServer::on_actionStartServer_triggered()
{
    this->dialog.show();
}

void ChatProgramServer::on_exitActionButton_triggered()
{
    exit(0);
}
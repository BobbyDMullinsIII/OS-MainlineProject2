#include <vector>
#include <thread>
#include "User.h"
#include "ChatProgramServer.h"
#include "InitServerDialog.h"
#include "Server.h"
#include "ServerController.h"

ChatProgramServer::ChatProgramServer(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this); //Sets up this window for the server

    //Sets absolute object names
    ui.sentTextObject->setObjectName("sentTextObject");
    ui.incomingTextObject->setObjectName("incomingTextObject");
    ui.clientTextObject->setObjectName("clientTextObject");

    //Set all strings to empty for now
    this->incomeString = "";       //Big string for appending all incoming messages to for display on ui (incomingTextObject)
    this->sentString = "";         //Big string for appending all incoming messages to for display on ui (sentTextObject)
    this->userDisplayString = "";  //Big string for displaying all currently connected clients on ui (clientTextObject)

    SControl = ServerController();

    QObject::connect(&dialog, SIGNAL(startServerSignal(std::string)), this, SLOT(RunServerProgram(std::string)), Qt::DirectConnection);
    QObject::connect(&SControl.server, SIGNAL(appendIncomeMessageSignal(std::string)), this, SLOT(appendIncomeMessage(std::string)), Qt::BlockingQueuedConnection);
    QObject::connect(&SControl.server, SIGNAL(appendSentMessageSignal(std::string)), this, SLOT(appendSentMessage(std::string)), Qt::BlockingQueuedConnection);
    QObject::connect(&SControl.server, SIGNAL(sendErrorMessage(bool, std::string, std::string)), this, SLOT(displayErrorMessage(bool, std::string, std::string)), Qt::BlockingQueuedConnection);
    QObject::connect(&SControl.server, SIGNAL(sendInfoMessage(std::string, std::string)), this, SLOT(displayInfoMessage(std::string, std::string)), Qt::BlockingQueuedConnection);
}

ChatProgramServer::~ChatProgramServer()
{}

void ChatProgramServer::AddUser(std::string userName, int userID)
{
    User newUser = User(userName, userID);
    this->userList.push_back(newUser);
    //Not done
}

void ChatProgramServer::RemoveUser(int userID)
{
    //Not done
}

//Method for running overall server program using threads
void ChatProgramServer::RunServerProgram(std::string port)
{
    //Creates master thread for loop so program doesnt freeze during infinite loop
    //2 threads so far - 1 for program main execution(GUI), 1 for server loop
    std::thread(&ServerController::RunServerLoop, &this->SControl, port).detach();
}

void ChatProgramServer::appendIncomeMessage(std::string incomeMessage)
{
    //Appends message to incomeString
    this->incomeString.append(incomeMessage + "\n\n");
    ui.incomingTextObject->append(QString::fromStdString(incomeMessage + "\n\n"));
}

void ChatProgramServer::appendSentMessage(std::string sentMessage)
{
    //Appends message to sentString
    this->sentString.append(sentMessage + "\n\n");
    ui.sentTextObject->append(QString::fromStdString(sentMessage + "\n\n"));
}

void ChatProgramServer::displayErrorMessage(bool doExit, std::string title, std::string text) 
{
    QMessageBox messageBox;
    messageBox.critical(0, title.c_str(), text.c_str());
    messageBox.setFixedSize(640, 480);

    if (doExit == true)
    {
        exit(0);
    }
}

void ChatProgramServer::displayInfoMessage(std::string title, std::string text)
{
    QMessageBox messageBox;
    messageBox.critical(0, title.c_str(), text.c_str());
    messageBox.setFixedSize(640, 480);
}

void ChatProgramServer::on_actionStartServer_triggered()
{
    this->dialog.show();
}

void ChatProgramServer::on_exitActionButton_triggered()
{
    WSACleanup(); //Method needed for Windows Sockets before program closes
    exit(0);
}
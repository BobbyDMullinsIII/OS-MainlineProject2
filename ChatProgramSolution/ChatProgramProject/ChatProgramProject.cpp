#include <vector>
#include <thread>
#include "User.h"
#include "ChatProgramProject.h"
#include "ConnectDialog.h"
#include "Client.h"
#include "ClientController.h"

ChatProgramProject::ChatProgramProject(QWidget* parent) : QMainWindow(parent)
{
    ui.setupUi(this); //Sets up this window for the client
 
    //Sets absolute object names
    ui.sentTextBrowser->setObjectName("sentTextBrowser");
    ui.incomingTextBrowser->setObjectName("incomingTextBrowser");
    ui.clientTextBrowser->setObjectName("clientTextBrowser");

    //Set all strings to empty for now
    this->incomeString = "";       //Big string for appending all incoming messages to for display on ui (incomingTextObject)
    this->sentString = "";         //Big string for appending all incoming messages to for display on ui (sentTextObject)
    this->userDisplayString = "";  //Big string for displaying all currently connected clients on ui (clientTextObject)

    CControl = ClientController();

    QObject::connect(&dialog, SIGNAL(startClientSignal(std::string, std::string, std::string)), this, SLOT(RunClientProgram(std::string, std::string, std::string)), Qt::DirectConnection);
    QObject::connect(&CControl.client, SIGNAL(sendNewClientListSignal(std::string)), this, SLOT(replaceClientList(std::string)), Qt::DirectConnection);
    QObject::connect(&CControl.client, SIGNAL(appendSentMessageSignal(std::string)), this, SLOT(appendSentMessage(std::string)), Qt::DirectConnection);
    QObject::connect(&CControl.client, SIGNAL(appendIncomeMessageSignal(std::string)), this, SLOT(appendIncomeMessage(std::string)), Qt::DirectConnection);
    QObject::connect(&CControl.client, SIGNAL(sendErrorMessage(bool, std::string, std::string)), this, SLOT(displayErrorMessage(bool, std::string, std::string)), Qt::BlockingQueuedConnection);
    QObject::connect(&CControl.client, SIGNAL(sendInfoMessage(std::string, std::string)), this, SLOT(displayInfoMessage(std::string, std::string)), Qt::DirectConnection);
}

ChatProgramProject::~ChatProgramProject()
{}

//Method for running overall client connection program using a thread to separate GUI from message loop
void ChatProgramProject::RunClientProgram(std::string port, std::string hostname, std::string username)
{
    //Creates master thread for loop so program doesnt freeze during infinite loop
    //2 threads total - 1 for program main execution(GUI), 1 for client message send/receive loop
    std::thread(&ClientController::RunClientLoop, &this->CControl, port, hostname, username).detach(); //THIS GIVES AN ERROR FOR SOME REASON
}

void ChatProgramProject::replaceClientList(std::string newList)
{
    //Replaces contents of clientTextBrowser
    ui.clientTextBrowser->setPlainText(QString::fromStdString(newList));
}

void ChatProgramProject::appendSentMessage(std::string sentMessage)
{
    //Appends message to sentString
    this->sentString.append(sentMessage + "\n\n");
    ui.sentTextBrowser->append(QString::fromStdString(sentMessage + "\n\n"));
}

void ChatProgramProject::appendIncomeMessage(std::string incomeMessage)
{
    //Appends message to incomeString
    this->incomeString.append(incomeMessage + "\n\n");
    ui.incomingTextBrowser->append(QString::fromStdString(incomeMessage + "\n\n"));
}

void ChatProgramProject::displayErrorMessage(bool doExit, std::string title, std::string text)
{
    QMessageBox messageBox;
    messageBox.critical(0, title.c_str(), text.c_str());
    messageBox.setFixedSize(640, 480);

    if (doExit == true)
    {
        exit(0);
    }
}

void ChatProgramProject::displayInfoMessage(std::string title, std::string text)
{
    QMessageBox messageBox;
    messageBox.critical(0, title.c_str(), text.c_str());
    messageBox.setFixedSize(640, 480);
}

void ChatProgramProject::on_messageSendButton_clicked()
{
    std::string messageText = ui.messageSendTextEdit->toPlainText().toStdString(); //Get message to send from server and convert to normal string
    this->CControl.sendMessage(messageText);
}

void ChatProgramProject::on_actionConnectToServer_triggered()
{
    this->dialog.show();
}

void ChatProgramProject::on_exitActionButton_triggered()
{
    WSACleanup(); //Method needed for Windows Sockets before program closes
    exit(0);
}
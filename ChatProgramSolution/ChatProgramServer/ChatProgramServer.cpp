#include <vector>
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
}

ChatProgramServer::~ChatProgramServer()
{}

void ChatProgramServer::on_actionStartServer_triggered()
{
    this->dialog.show();
}

void ChatProgramServer::on_exitActionButton_triggered()
{
    exit(0);
}

void ChatProgramServer::AddUser(std::string userName, int userID)
{
    User newUser = User(userName, userID);
    this->userList.push_back(newUser);
}

void ChatProgramServer::RemoveUser(int userID)
{

}
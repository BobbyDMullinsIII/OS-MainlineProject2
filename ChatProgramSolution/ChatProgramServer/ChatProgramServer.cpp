#include "ChatProgramServer.h"
#include "ServerController.h"

ChatProgramServer::ChatProgramServer(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this); //Sets up this window for the server

    QMainWindow::setStyleSheet("background-color: lightblue; color: black;"); //Sets background color of window to gray and text to white
}

ChatProgramServer::~ChatProgramServer()
{}

void ChatProgramServer::on_exitActionButton_triggered()
{
    exit(0);
}
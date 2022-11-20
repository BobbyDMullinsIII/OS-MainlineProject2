#include "ChatProgramServer.h"

ChatProgramServer::ChatProgramServer(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this); //Sets up this window for the server

    QMainWindow::setStyleSheet("background-color: blue; color: white;"); //Sets background color of window to gray and text to white

    //connect(exitActionButton, SIGNAL(clicked()), this, SLOT(handleExitButton()));//Set exit button to close server program
}

ChatProgramServer::~ChatProgramServer()
{}

void ChatProgramServer::handleExitButton()
{
    ChatProgramServer::close();
}
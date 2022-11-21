#include "ChatProgramServer.h"
#include "InitServerDialog.h"
#include "ServerController.h"

ChatProgramServer::ChatProgramServer(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this); //Sets up this window for the server

    QMainWindow::setStyleSheet("background-color: lightblue; color: black;"); //Sets background color of window to light blue and text to black
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
#include "ChatProgramProject.h"
#include "ConnectDialog.h"
#include "ClientController.h"

ChatProgramProject::ChatProgramProject(QWidget* parent) : QMainWindow(parent)
{
    ui.setupUi(this); //Sets up this window for the client
 
}

ChatProgramProject::~ChatProgramProject()
{}

void ChatProgramProject::on_actionConnectToServer_triggered()
{
    this->dialog.show();
}

void ChatProgramProject::on_exitActionButton_triggered()
{
    exit(0);
}
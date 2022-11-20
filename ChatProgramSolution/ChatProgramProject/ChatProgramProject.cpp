#include "ChatProgramProject.h"

ChatProgramProject::ChatProgramProject(QWidget* parent) : QMainWindow(parent)
{
    ui.setupUi(this); //Sets up this window for the client
 
    QMainWindow::setStyleSheet("background-color: gray; color: white;"); //Sets background color of window to gray and text to white

    //connect(exitActionButton, SIGNAL(clicked()), this, SLOT(handleExitButton()));//Set exit button to close client program
}

ChatProgramProject::~ChatProgramProject()
{}

void ChatProgramProject::handleExitButton()
{
    ChatProgramProject::close();
}
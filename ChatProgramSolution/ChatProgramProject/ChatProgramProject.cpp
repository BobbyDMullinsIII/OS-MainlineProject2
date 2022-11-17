#include "ChatProgramProject.h"

ChatProgramProject::ChatProgramProject(QWidget* parent) : QMainWindow(parent)
{
    ui.setupUi(this); //Sets up this window

    //Stylesheets for Qt windows and widgets are VERY similar to CSS
    QMainWindow::setStyleSheet("background-color: black; color: white;");//Sets background color of window to black and text to white

    //Will figure this out later
    //connect(exitActionButton, SIGNAL(clicked()), this, SLOT(handleExitButton()));//Set exit button to close program

}

ChatProgramProject::~ChatProgramProject()
{}

void ChatProgramProject::handleExitButton()
{
    ChatProgramProject::close();
}
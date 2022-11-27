#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ChatProgramProject.h"

#include <vector>
#include "User.h"
#include "ConnectDialog.h"
#include "ClientController.h"
#include "ChatProgramProject.h"

class ChatProgramProject : public QMainWindow
{
    Q_OBJECT

public:
    ChatProgramProject(QWidget *parent = nullptr);
    ~ChatProgramProject();

    ConnectDialog dialog;
    std::string incomeString;       //Big string for appending all incoming messages to for display on ui (incomingTextObject)
    std::string sentString;         //Big string for appending all incoming messages to for display on ui (sentTextObject)
    std::string userDisplayString;  //Big string for displaying all currently connected clients on ui (clientTextObject)
    ClientController CControl;

public slots:
    void RunClientProgram(std::string port, std::string hostname, std::string username);
    void appendSentMessage(std::string sentMessage);
    void appendIncomeMessage(std::string incomeMessage);
    void displayErrorMessage(bool doExit, std::string title, std::string text);
    void displayInfoMessage(std::string title, std::string text);

private slots:
    void on_actionConnectToServer_triggered();
    void on_exitActionButton_triggered(); //Buttons in the menubar menus use the "triggered" event
                                          //Regular buttons on the form might use the "clicked" event instead

private:
    Ui::ChatProgramProjectClass ui;
};

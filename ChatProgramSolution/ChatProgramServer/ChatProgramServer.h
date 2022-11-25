#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ChatProgramServer.h"

#include <vector>
#include "User.h"
#include "InitServerDialog.h"
#include "ServerController.h"
#include "ChatProgramServer.h"

class ChatProgramServer : public QMainWindow
{
    Q_OBJECT

public:
    ChatProgramServer(QWidget *parent = nullptr);
    ~ChatProgramServer();

    void AddUser(std::string userName, int userID);
    void RemoveUser(int userID);

    InitServerDialog dialog;
    std::string incomeString;       //Big string for appending all incoming messages to for display on ui (incomingTextObject)
    std::string sentString;         //Big string for appending all incoming messages to for display on ui (sentTextObject)
    std::string userDisplayString;  //Big string for displaying all currently connected clients on ui (clientTextObject)
    std::vector<User> userList;     //Vector of users and/or clients currently connected to server (Will modify userDisplayString when changed)
    ServerController SControl;

public slots:
    void RunServerProgram(std::string port);
    void appendIncomeMessage(std::string incomeMessage);
    void appendSentMessage(std::string sentMessage);

private slots:
    void on_actionStartServer_triggered();
    void on_exitActionButton_triggered(); //Buttons in the menubar menus use the "triggered" event
                                          //Regular buttons on the form might use the "clicked" event instead

private:
    Ui::ChatProgramServerClass ui;
};

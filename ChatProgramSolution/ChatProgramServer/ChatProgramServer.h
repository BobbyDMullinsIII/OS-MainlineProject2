#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ChatProgramServer.h"
#include "InitServerDialog.h"
#include "ServerController.h"

class ChatProgramServer : public QMainWindow
{
    Q_OBJECT

public:
    ChatProgramServer(QWidget *parent = nullptr);
    ~ChatProgramServer();

    InitServerDialog dialog;
    ServerController SControl;

private slots:
    void on_actionStartServer_triggered();
    void on_exitActionButton_triggered(); //Buttons in the menubar menus use the "triggered" event
                                          //Regular buttons on the form might use the "clicked" event instead

private:
    Ui::ChatProgramServerClass ui;
};

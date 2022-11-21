#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ChatProgramProject.h"
#include "ClientController.h"

class ChatProgramProject : public QMainWindow
{
    Q_OBJECT

public:
    ChatProgramProject(QWidget *parent = nullptr);
    ~ChatProgramProject();

    ClientController CControl; //Client Controller Class

private slots:
    void on_exitActionButton_triggered(); //Buttons in the menubar menus use the "triggered" event
                                          //Regular buttons on the form might use the "clicked" event instead

private:
    Ui::ChatProgramProjectClass ui;
};

#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ChatProgramServer.h"

class ChatProgramServer : public QMainWindow
{
    Q_OBJECT

public:
    ChatProgramServer(QWidget *parent = nullptr);
    ~ChatProgramServer();

private slots:
    void handleExitButton();

private:
    Ui::ChatProgramServerClass ui;
};

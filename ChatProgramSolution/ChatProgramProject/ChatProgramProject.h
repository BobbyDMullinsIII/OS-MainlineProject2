#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ChatProgramProject.h"

class ChatProgramProject : public QMainWindow
{
    Q_OBJECT

public:
    ChatProgramProject(QWidget *parent = nullptr);
    ~ChatProgramProject();

private slots:
    void handleExitButton();

private:
    Ui::ChatProgramProjectClass ui;
};

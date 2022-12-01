/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Solution/Project:   ChatProgramSolution/ChatProgramServer
//  File Name:          main.cpp
//  Description:        Main file for Operating Systems Mainline Project 2 Server (Client-Server Chat Program)
//  Course:             CSCI-4727-001 - Operating Systems
//  Authors:            Bobby Mullins, Isaiah Jayne, Jacob Manis, Zachary Lykins       
//  Created:            Sunday, November 19, 2022
//  Copyright:          Mainline Team 1 - Operating Systems
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ChatProgramServer.h"
#include <qmessagebox.h>
#include <QtWidgets/QApplication>
#pragma comment(lib, "Ws2_32.lib")

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Run server program
    ChatProgramServer swindow; //Main GUI of server program (Using Qt)
    swindow.show(); //Show main server GUI window

    return a.exec();
}

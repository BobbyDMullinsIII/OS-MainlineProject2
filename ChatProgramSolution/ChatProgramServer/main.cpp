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

    //Variables and section of code is needed for Windows Sockets
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;

    wVersionRequested = MAKEWORD(2, 2);
    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0)
    {
        //String to put into messagebox
        std::string message = "There was an error with WSAStartup in the server. \nError: ";
        message += std::to_string(err);

        QMessageBox messageBox;
        messageBox.critical(0, "Server WSAStartup Error", message.c_str());
        messageBox.setFixedSize(640, 480);

        return 1;
    }

    //Run server program
    ChatProgramServer swindow; //Main GUI of server program (Using Qt)
    swindow.show(); //Show main server GUI window

    WSACleanup(); //Method needed for Windows Sockets before program closes

    return a.exec();
}

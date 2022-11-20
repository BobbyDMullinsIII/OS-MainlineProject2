/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Solution/Project:   ChatProgramSolution/ChatProgramProject
//  File Name:          main.cpp
//  Description:        Main file for Operating Systems Mainline Project 2 Client (Client-Server Chat Program)
//  Course:             CSCI-4727-001 - Operating Systems
//  Authors:            Bobby Mullins, Isaiah Jayne, Jacob Manis, Zachary Lykins       
//  Created:            Thursday, November 3, 2022
//  Copyright:          Mainline Team 1 - Operating Systems
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ClientController.h"
#include <QtWidgets/QApplication>
#pragma comment(lib, "Ws2_32.lib")

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Run client program
    ClientController CControl;
    CControl.RunClientProgram();

    return a.exec();
}

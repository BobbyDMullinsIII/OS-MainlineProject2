#pragma once

//Includes taken from example client.cc file (And Windows equivalents)
#include <stdlib.h>
#include <io.h>
#include <Winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string.h>

//Normal includes
#include <string>
#include <qmessagebox.h>
#include <QObject>
#include <QVariant>
#include "CopyableQObject.h"
#include "User.h"
#include "Client.h"

class Client : public CopyableQObject
{
    Q_OBJECT
public:
    Client();
    ~Client();

    char hostname[81];
    struct addrinfo* myinfo;
    int sockdesc;
    char portnum[81];
    int connection;
    int value;
    std::string username;

    void InitializeClient(std::string port, std::string hostname);
    void createHostName(std::string host);
    void createPortNum(std::string port);
    void createSockDesc();
    void createAddressRecord();
    void connectToHost();

    void sendNewClientListUI(std::string newList);
    void sendSentMessageUI(std::string smessage);
    void sendIncomeMessageUI(std::string imessage);
    void sendError(bool doExit, std::string title, std::string text);
    void sendInfo(std::string title, std::string text);

    Q_SIGNAL void sendNewClientListSignal(std::string newList);
    Q_SIGNAL void appendSentMessageSignal(std::string sentMessage);
    Q_SIGNAL void appendIncomeMessageSignal(std::string incomeMessage);
    Q_SIGNAL void sendErrorMessage(bool exit, std::string title, std::string text);
    Q_SIGNAL void sendInfoMessage(std::string title, std::string text);

private:

};

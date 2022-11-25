#pragma once

#include <string>
#include <vector>
#include <QObject>
#include <QVariant>
#include "CopyableQObject.h"
#include "Server.h"
#include "ServerController.h"

class ServerController : public CopyableQObject
{
    Q_OBJECT

public:
    ServerController();
    ServerController(const ServerController& s);
    ~ServerController();

    Q_SIGNAL void appendIncomeMessageSignal(std::string incomeMessage);
    Q_SIGNAL void appendSentMessageSignal(std::string sentMessage);

    void RunServerLoop(std::string port);
    void HandleClient(int connection);

private:
};
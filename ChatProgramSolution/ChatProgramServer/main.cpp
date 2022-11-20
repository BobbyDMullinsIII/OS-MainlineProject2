#include "ChatProgramServer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChatProgramServer w;
    w.show();
    return a.exec();
}

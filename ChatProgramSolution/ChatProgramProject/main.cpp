#include "ChatProgramProject.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChatProgramProject w;
    w.show();
    return a.exec();
}

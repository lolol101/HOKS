#include "authorizationWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    authorizationWindow w;
    w.show();
    return a.exec();
}

#include "authorizationWindow.h"
#include <appstyle.h>

#include <QApplication>
#include <MainWindow.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    authorizationWindow w;
    w.show();
    return a.exec();
}

#include "authorizationWindow.h"
#include <appstyle.h>

#include <QApplication>
#include <MainWindow.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    authorizationWindow w;
    w.show();
//    MainWindow w;
//    w.show_main_window();
    return a.exec();
}

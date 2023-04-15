#include "authorizationWindow.h"
#include <appstyle.h>

#include <QApplication>
#include <MainWindow.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    authorizationWindow w;
//    w.show();
//    w.show_registration();
    MainWindow w;
    w.show_main_window();
    w.show_creation_new_room();
    for (int i = 0; i < 50; ++i) {
        w.show_checkbox("Ilia");
    }
//    w.show_creation_new_room();
    return a.exec();
}

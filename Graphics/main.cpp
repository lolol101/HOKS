#include "appGraphic.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    appGraphic w;
    w.show();
    return a.exec();
}

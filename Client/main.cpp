#include <QApplication>
#include "client.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Client client;
    client.start();
    return a.exec();
}

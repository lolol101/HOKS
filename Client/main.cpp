#include <QApplication>
#include "client.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Client client;
    client.connect_signals_to_slots();
    client.start();
    return a.exec();
}

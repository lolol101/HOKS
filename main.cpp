#include <QCoreApplication>
#include "database.h"
#include <QDebug>
#include <QProcess>
#include <QByteArray>

int main()
{


    db_space::Database tmp("QPSQL","127.0.0.1","database_qt","postgres","postgres");

    if (tmp.is_open()) {
        qDebug() << "OK\n";
        tmp.info_db();
    } else {
        qDebug() << "Error\n";
    }

    return 0;
}

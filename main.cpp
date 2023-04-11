#include <QCoreApplication>
#include "database.h"
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <QDebug>
#include <QProcess>


int main()
{


    db_space::Database tmp("QPSQL","127.0.0.1","database_qt","postgres","postgres");

    if (tmp.is_open()) {
        std::cout << "OK\n";
        tmp.info_db();
    } else {
        std::cout << "Error\n";
    }

//    QProcess *proc = new QProcess();
//    proc->start("/home/crytek/Study/HOKS/script.sh");

    QVector<QString> arr = tmp.get_username_of_users();
    for (auto &item: arr) {
        qDebug() << item;
    }
    return 0;
}

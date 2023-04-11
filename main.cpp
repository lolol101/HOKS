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

    tmp.change_array_chats_for_user("kola","2555");
    return 0;
}

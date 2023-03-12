#include <QCoreApplication>
#include "database.h"
#include <QDateTime>
#include <QDate>
#include <QTime>


int main()
{


    Database tmp("QPSQL","127.0.0.1","database_qt","postgres","postgres");

    if (tmp.is_open()) {
        std::cout << "OK\n";
        tmp.info_db();
    } else {
        std::cout << "Error\n";
    }

    return 0;
}

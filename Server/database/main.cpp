#include <QCoreApplication>
#include "database.h"
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <QDebug>


int main()
{


    db_space::Database tmp("QPSQL","127.0.0.1","database_qt","postgres","postgres");

    if (tmp.is_open()) {
        std::cout << "OK\n";
        tmp.info_db();
    } else {
        std::cout << "Error\n";
    }

//    QString res = tmp.get_data_from_chats(1,db_space::CHATS::ARRAY_PEOPLE);
    bool result = tmp.change_data_in_chats(1,db_space::CHATS::NAME, "telegram");
    qDebug() << result << '\n';

    return 0;
}

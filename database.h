#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlError>
#include <QDateTime>
#include <QString>
#include <iostream>

class Database
{
public:
    Database(QString driver,
             QString host,
             QString db_name,
             QString user_name,
             QString password);

    bool is_open();
    void info_db();
    bool registerUser(QString table,
                    QString username,
                    QString password,
                    QString email,
                    QString first_name,
                    QString last_name);
    bool check_user_in_bd(QString username,QString table);
    bool check_pass_by_username(QString username, QString pass,QString table);
private:
   QSqlDatabase obj;
   QString driver;
   QString host;
   QString db;
   QString user;
   QString pass;
   bool is_open_;

   bool is_table_exist(QString table);
};

#endif // DATABASE_H

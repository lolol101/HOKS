#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlError>
#include <QDateTime>
#include <QString>
#include <QVector>
#include <iostream>
#include <QMap>

namespace db_space {

    enum class USER  {ID=1,USERNAME,PASSWORD,EMAIL,
                      CREATE_DATA,LAST_LOGIN,NAME,
                      SURNAME,CHAT_OF_USER,STATUS};

    enum class TABLE {USERS=1, CHATS, MESSAGES};

    enum class CHATS {NAME=1,ARRAY_PEOPLE};

    const QMap<TABLE, QString> enum_tables_to_string = {
        {TABLE::USERS, "users"},
        {TABLE::MESSAGES, "messages"},
        {TABLE::CHATS, "chats"}
    };

    const QMap<USER, QString> enum_commands_to_string = {
        {USER::ID, "user_id"},
        {USER::USERNAME, "username"},
        {USER::PASSWORD, "password"},
        {USER::EMAIL, "email"},
        {USER::CREATE_DATA, "created_on"},
        {USER::LAST_LOGIN, "last_login"},
        {USER::NAME, "first_name"},
        {USER::SURNAME, "last_name"},
        {USER::CHAT_OF_USER, "chat_of_users"},
        {USER::STATUS, "status"}
    };

    const QMap<CHATS, QString> enum_chats_to_string = {
        {CHATS::NAME, "name_or_private"},
        {CHATS::ARRAY_PEOPLE, "people"}
    };

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
        bool registration(QString username,
                        QString password,
                        QString email,
                        QString first_name,
                        QString last_name);

        QString authorization(QString username,
                           QString password);
        QString get_data_from_users(QString username, USER column);
        bool change_data_in_users(QString username, USER column, QString new_data);
        QString get_data_from_chats(int chat_id, CHATS column);
        bool change_data_in_chats(int chat_id, CHATS column, QString new_data);

        //TODO
//        bool delete_account();
//        bool send_message();


//        QVector<QString> get_all_messages_from_chat();
//        QVector<QString> get_other_usernames_in_this_chat();
//        bool delete_chat();
//        bool delete_message();
//        bool edit_message();
        //-------------------------------
        bool check_user_in_bd(QString username);
        bool check_pass_by_username(QString username, QString pass);
    private:
       QSqlDatabase obj;
       QString driver;
       QString host;
       QString db;
       QString user;
       QString pass;
       bool is_open_;
    };
}
#endif // DATABASE_H

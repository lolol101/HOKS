#include "database.h"
#include <QDebug>
namespace db_space {
    Database::Database(QString type_driver,
                       QString hostname,
                       QString db_name,
                       QString user_name,
                       QString password)
    {
        driver = type_driver;
        host = hostname;
        db = db_name;
        user = user_name;
        pass = password;

        obj = QSqlDatabase::addDatabase(driver);
        obj.setHostName(host);
        obj.setDatabaseName(db);
        obj.setUserName(user);
        obj.setPassword(pass);
        is_open_ = obj.open();
    }

    bool Database::is_open() {
        return is_open_;
    }

    void Database::info_db() {
        qDebug() << "Database: " << host <<
                     "\nHost: " << host <<
                     "\nUser: " << user << '\n';
    }

    bool Database::registration(
                              QString username,
                              QString password,
                              QString email,
                              QString first_name,
                              QString last_name) {
        //true - OK
        //false - username is not unique or table is not correct

        QSqlQuery query(obj);
        const QString dt = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

        query.prepare("INSERT INTO users(username,password,email,created_on,first_name,last_name)"
                      " VALUES(:user, :pass, :em, :dt, :first, :last)");
        query.bindValue(":user",username);
        query.bindValue(":pass",password);
        query.bindValue(":em",email);
        query.bindValue(":dt",dt);
        query.bindValue(":first",first_name);
        query.bindValue(":last",last_name);

        bool status_transaction = query.exec();
        if (!status_transaction) {
            qDebug() << query.lastError() << '\n';
        }
        return status_transaction;
    }

    QString Database::authorization(QString username, QString password)
    {
        if (!check_user_in_bd(username)) {
            return "user doesnt exist";
        }
        if (!check_pass_by_username(username,password)) {
            return "password is not correct";
        }
        return "Authorization is sucsessful";
    }

    QString Database::get_data_from_users(QString username, USER column)
    {
        QSqlQuery query(obj);
        query.exec("SELECT " + enum_commands_to_string.value(column)
                                             + " FROM users WHERE username = '"+username+"'");
        query.next();
        return query.value(0).toString();
    }

    bool Database::change_data_in_users(QString username, USER column, QString new_data)
    {
        QSqlQuery query(obj);
        bool status_transaction = query.exec("UPDATE users SET " + enum_commands_to_string.value(column)
                                             + " = '" + new_data + "'");

        if (!status_transaction) {
            return false;
        } else {
            return true;
        }
    }

    QString Database::get_data_from_chats(int chat_id, CHATS column)
    {
        QSqlQuery query(obj);
        query.exec("SELECT "+enum_chats_to_string.value(column)
                   + " FROM chats WHERE chat_id = "+QString::number(chat_id));

        query.next();
        return query.value(0).toString();
    }

    bool Database::change_data_in_chats(int chat_id, CHATS column, QString new_data)
    {
        QSqlQuery query(obj);
        bool status_transaction = query.exec("UPDATE chats SET " + enum_chats_to_string.value(column)
                                             + " = '" + new_data + "'");

        if (!status_transaction) {
            return false;
        } else {
            return true;
        }
    }

//    bool Database::delete_account()
//    {

//    }

//    bool Database::send_message()
//    {

//    }

//    QVector<QString> Database::get_all_messages_from_chat()
//    {

//    }

//    QVector<QString> Database::get_other_usernames_in_this_chat()
//    {

//    }

    bool Database::check_user_in_bd(QString username) {
        //true - user is already registered
        //false - user is not in database
        QSqlQuery query(obj);
        bool status_transaction = query.exec("SELECT COUNT(*) as counter FROM users WHERE username = '"
                                             +username+"'");
        if (!status_transaction) {
            qDebug() << query.lastError() << '\n';
        }
        query.next();
        int value = query.value(0).toInt();
        return (value == 1);
    }

    bool Database::check_pass_by_username(QString username, QString pass) {
        //true - user has this password or user does not exist
        //false - user has another password (!!!)
        if (!check_user_in_bd(username)) {
            qDebug() << "Username: " + username + " does not exist\n";
        }
        QSqlQuery query(obj);
        bool status_transaction = query.exec("SELECT * FROM users WHERE username = '"+username+"'");

        if (!status_transaction) {
            qDebug() << query.lastError() << '\n';
        }
        query.next();
        QString bd_pass = query.value(2).toString();
        return (bd_pass == pass);
    }
}

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
                                             + " = '" + new_data + "' WHERE username ='"+username+"'");

        if (!status_transaction) {
            return false;
        } else {
            return true;
        }
    }

    void Database::change_array_chats_for_user(QString username, QString new_data)
    {
        QSqlQuery query(obj);
        QStringList tmp = get_array_of_chat_id_for_user(username);

        if (tmp[0] == "") {

            query.exec("UPDATE users SET chat_of_users = '{"+new_data
                       +"}' WHERE username = '"+username+"'");
        } else {
            tmp.append(new_data);
            query.exec("UPDATE users SET chat_of_users = '{"+tmp.join(",")
                       +"}' WHERE username = '"+username+"'");
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

    QStringList Database::get_array_of_chat_id_for_user(QString username)
    {
        QStringList array;
        QString tmp_string;
        QSqlQuery query(obj);

        query.exec("SELECT chat_of_users FROM users WHERE username = '"+username+"'");
        query.next();

        tmp_string = query.value(0).toString();
        tmp_string.remove(0,1);
        tmp_string.remove(tmp_string.size()-1,1);

        array = tmp_string.split(',');
        return array;
    }

    QStringList Database::get_array_of_users_in_chat(int id)
    {
        QStringList array;
        QString tmp_string;
        QSqlQuery query(obj);

        query.exec("SELECT people FROM chats WHERE chat_id = '"+QString::number(id)+"'");
        query.next();

        tmp_string = query.value(0).toString();
        tmp_string.remove(0,1);
        tmp_string.remove(tmp_string.size()-1,1);

        array = tmp_string.split(',');
        return array;
    }

    int Database::create_chat(QString name_or_private, QStringList people)
    {
        //return chat_id
        QSqlQuery query(obj);
        query.exec("INSERT INTO chats (chat_id,name_or_private,people) VALUES(DEFAULT,'"+
                                  name_or_private+"','{"+ people.join(',')+"}') RETURNING chat_id");
        query.next();
        return query.value(0).toInt();
    }

    void Database::delete_chat(int id)
    {
        QSqlQuery query(obj);
        //get users in this chat
        QStringList tmp_list;
        QStringList users = get_array_of_users_in_chat(id);
        for (auto& item: users) {
            tmp_list = get_array_of_chat_id_for_user(item);
            tmp_list.removeOne(QString::number(id));
            query.exec("UPDATE users SET chat_of_users = '{"
                       +tmp_list.join(',')+"}' WHERE username = '"
                       +item+"'");
        }
        //deleting messages in table messages
        query.exec("DELETE FROM messages WHERE chat_id = "+QString::number(id));
        //deleting chat
        query.exec("DELETE FROM chats WHERE chat_id = "+QString::number(id));
    }

    void Database::delete_account(QString username)
    {
        QSqlQuery query(obj);

        //rename author in messages with DELETED
        query.exec("UPDATE messages SET author = 'DELETED' WHERE author = '"+username+"'");

        //deleting account from chats
        QStringList tmp_array;
        QStringList array = get_array_of_chat_id_for_user(username);
        for (auto& chat: array) {
            tmp_array = get_array_of_users_in_chat(chat.toInt());
            tmp_array.removeOne(username);
            query.exec("UPDATE chats SET people = '{"
                       +tmp_array.join(',')
                       +"}' WHERE chat_id = "+chat);
        }

        //deleting account from user
        query.exec("DELETE FROM users WHERE username = '"+username+"'");
    }

    QVector<msg> Database::get_all_msg_from_chat(int id)
    {
        QSqlQuery query(obj);
        query.exec("SELECT author,time,text_message,media FROM messages WHERE number_chat = "+QString::number(id)+" ORDER BY time ASC");

        QVector<msg> array(query.size());
        for (int i = 0; i < static_cast<int>(query.size()); i++) {
            query.next();
            array[i] = msg(query.value(0).toString(),
                           query.value(1).toString(),
                           query.value(2).toString(),
                           query.value(3).toBool());
        }
        return array;
    }

    QVector<QString> Database::get_username_of_users()
    {
        QSqlQuery query(obj);
        query.exec("SELECT username FROM users");

        QVector<QString> array(query.size());
        for (int i = 0; i < static_cast<int>(query.size()); i++) {
            query.next();
            array[i] = QString(query.value(0).toString());
        }
        return array;
    }

    void Database::insert_message(int number_chat, QString author, QString text_msg, bool media)
    {
        QSqlQuery query(obj);
        query.exec("INSERT INTO messages (msg_id,number_chat,time,author,text_message,media) VALUES(DEFAULT,"
                   +QString::number(number_chat)+",'"+get_time_db()
                   +"','"+author+"','"+text_msg+"','"+QString::number(static_cast<int>(media)) +"')");
    }

    void Database::delete_message(int msg_id)
    {
        QSqlQuery query(obj);
        query.exec("DELETE FROM messages WHERE msg_id = "+QString::number(msg_id));
    }

    void Database::edit_message(int msg_id, QString new_msg)
    {
        QSqlQuery query(obj);
        query.exec("UPDATE messages SET text_message = '"
                   +new_msg+"' WHERE msg_id = "+QString::number(msg_id));
    }

    QString Database::get_time_db()
    {
        QDateTime dt = QDateTime::currentDateTime();
        QString format = QString::number(dt.date().year())+"-"
                +QString::number(dt.date().month())+"-"
                +QString::number(dt.date().day())+" "
                +dt.time().currentTime().toString();
        return format;
    }

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

    msg::msg(QString author_, QString time_, QString text_, bool media_): author(std::move(author_)),time(std::move(time_)),text_message(std::move(text_)),media(media_){}

}

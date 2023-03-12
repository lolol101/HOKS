#include "database.h"

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

bool Database::is_table_exist(QString table) {

    QStringList list = obj.tables(QSql::Tables);
    QStringList::iterator Iter = list.begin();
    while (Iter != list.end()) {
        if (*Iter == table) {
            return true;
        }
        ++Iter;
    }
    return false;
}

bool Database::registerUser(QString table,
                          QString username,
                          QString password,
                          QString email,
                          QString first_name,
                          QString last_name) {
    //true - OK
    //false - username is not unique or table is not correct
    if (!is_table_exist(table)) {
        qDebug() << table << " doesnt exist\n";
        return false;}
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

bool Database::check_user_in_bd(QString username,QString table) {
    //true - user is already registered
    //false - user is not in database
    QSqlQuery query(obj);
    bool status_transaction = query.exec("SELECT COUNT(*) as counter FROM "+table+" WHERE username = '"+username+"'");
    if (!status_transaction) {
        qDebug() << query.lastError() << '\n';
    }
    query.next();
    int value = query.value(0).toInt();
    return (value == 1);
}

bool Database::check_pass_by_username(QString username, QString pass,QString table) {
    //true - user has this password or user does not exist
    //false - user has another password (!!!)
    if (!check_user_in_bd(username, table)) {
        qDebug() << "Username: " + username + " does not exist\n";
    }
    QSqlQuery query(obj);
    bool status_transaction = query.exec("SELECT * FROM "+table+" WHERE username = '"+username+"'");

    if (!status_transaction) {
        qDebug() << query.lastError() << '\n';
    }
    query.next();
    QString bd_pass = query.value(2).toString();
    return (bd_pass == pass);
}

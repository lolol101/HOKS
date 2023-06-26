#include "server.h"

bool check_reg_exp(const QRegExp& re, const QString& str) {
    return (re.exactMatch(str));
}

template<class T>
QByteArray Server::make_byte_message(const Command &command, const QVector<T>& arguments) {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0 << quint8(command);
    for (const auto& item : arguments)
        out << item;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    return block;
}

QByteArray Server::make_byte_message(const Command &command, const QString& file_name, const QByteArray& bytes) {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0 << quint8(command);
    out << file_name << bytes.size() << bytes;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    return block;
}

Server::Server() : data_base("QPSQL", "127.0.0.1", "database_qt", "postgres", "postgres") {}

void Server::start() {
    if (this->listen(QHostAddress("185.125.201.130"), 1101)) {
        qDebug() << "Start\n";
        connect(this, &QTcpServer::newConnection, this, &Server::new_connection);
    }
    else
        qDebug() << "Error\n";
}

void Server::new_connection() {
    QTcpSocket* socket = this->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, this, &Server::slot_ready_read);
    socket->write(make_byte_message(Command::checkConnection, QVector<int>{}));
}


void Server::slot_ready_read() {
    QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
    QDataStream in(socket);
    if (in.status() == QDataStream::Ok) {
        while (true) {
            if (clients_msg_size[socket] == 0) {
                if (socket->bytesAvailable() < 2)
                    break;
                in >> clients_msg_size[socket];
            }
            if (socket->bytesAvailable() < clients_msg_size[socket])
                break;
            clients_msg_size[socket] = 0;
            quint8 command;
            in >> command;
            switch (command) {
                case Command::checkAuthoriziatonData: {
                    QString login, password;
                    in >> login >> password;
                    QVector<QString> args(2);
                    if (!data_base.check_user_in_bd(login))
                        args[0] = "Пользователь не найден";
                    else if (!data_base.check_pass_by_username(login, password))
                        args[1] = "Неправильный пароль";
                    socket->write(make_byte_message(Command::checkAuthoriziatonData, args));
                    break;
                }
                case Command::checkRegistrationData: {
                    QString login, password, email, first_name, last_name;
                    in >> login >> password >> email >> first_name >> last_name;
                    QString login_error, password_error, email_error, first_name_error, last_name_error;
                    QVector<QString> errors;

                    if(!check_reg_exp(QRegExp("[A-Za-z0-9]+"), login))
                        login_error = "Некорректный логин";
                    if(!check_reg_exp(QRegExp("[A-Za-z0-9]{8,}"), password))
                        password_error = "Некорректный пароль";
                    if(!check_reg_exp(QRegExp("[A-Za-z0-9]+@[a-z]+.(com|ru|org|us)"), email))
                        email_error = "Некорректный email";
                    if(!check_reg_exp(QRegExp("[A-Z][a-z]+"), first_name))
                        first_name_error = "Некорректное имя";
                    if(!check_reg_exp(QRegExp("[A-Z][a-z]+"), last_name))
                        last_name_error = "Некорректная фамилия";

                    errors = {login_error, password_error, email_error, first_name_error, last_name_error};
                    socket->write(make_byte_message(Command::checkRegistrationData, errors));
                    break;
                }
                case Command::registrateUser: {
                    QString login, password, email, first_name, last_name;
                    in >> login >> password >> email >> first_name >> last_name;
                    data_base.registration(login, password, email, first_name, last_name);
                    break;
                }
                case Command::appendMessage: {
                    QString message, id, user_name, media_flag;
                    in >> message >> id >> user_name >> media_flag;
                    QStringList people_names = data_base.get_array_of_users_in_chat(id.toInt());
                    data_base.insert_message(id.toInt(), user_name, message, static_cast<bool>(media_flag.toInt()));
                    for (const auto& item : people_names) {
                        if (sockets.find(item) != sockets.end() && user_name != item)
                            sockets[item]->write(make_byte_message(Command::otherUserMessage, QVector<QString>{message, id, user_name, media_flag}));
                    }
                    break;
                }
                case Command::uploadFile: {
                    QString file_name;
                    int size;
                    in >> file_name >> size;
                    in.skipRawData(4);
                    QByteArray bytes;
                    bytes.resize(size);
                    in.readRawData(bytes.data(), size);
                    QFile file("./Files/" + file_name);
                    file.open(QIODevice::WriteOnly);
                    file.write(bytes, size);
                    break;
                }
                case Command::userEnterApp: {
                    QString user_name;
                    in >> user_name;
                    sockets[user_name] = socket;
                    break;
                }
                case Command::getRooms: {
                    QString user_name;
                    in >> user_name;
                    QVector<QPair<QString, QString>> args;
                    QStringList ids = data_base.get_array_of_chat_id_for_user(user_name);
                    for (const auto& item : ids)
                        args.push_back(QPair(item, data_base.get_data_from_chats(item.toInt(), db_space::CHATS::NAME)));
                    socket->write(make_byte_message(Command::getRooms, args));
                    break;
                }
                case Command::appendRoom: {
                    QString room_name;
                    QString item;
                    in >> room_name;
                    QVector<QString> people_list;
                    while (!in.atEnd()) {
                        in >> item;
                        people_list.push_back(item);
                    }
                    int id = data_base.create_chat(room_name, people_list.toList());
                    for (const auto& item : people_list)
                        data_base.change_array_chats_for_user(item, QString::number(id));
                    for (const auto& item : people_list) {
                        if (sockets.find(item) != sockets.end())
                            sockets[item]->write(make_byte_message(Command::roomCreated, QVector<QString>{room_name, QString::number(id)}));
                    }
                    break;
                }
                case Command::getAllUsers: {
                    QVector<QString> users_names = data_base.get_username_of_users();
                    users_names.push_front(QString::number(users_names.size()));
                    socket->write(make_byte_message(Command::getAllUsers, users_names));
                    break;
                }
                case Command::loadMsgs: {
                    int room_id;
                    in >> room_id;
                    QVector<db_space::msg> msgs = data_base.get_all_msg_from_chat(room_id);
                    QVector<QVector<QString>> msgs_raw;
                    msgs_raw.push_back(QVector<QString>{QString::number(room_id)});
                    for (const auto& item : msgs)
                        msgs_raw.push_back(QVector<QString>{item.author, item.time, item.text_message, QString::number((int)item.media)});
                    socket->write(make_byte_message(Command::loadMsgs, msgs_raw));
                    break;
                }
                case Command::getFile: {
                    QString room_id, file_name;
                    in >> room_id >> file_name;
                    QFile file("./Files/" + QFileInfo(data_base.get_file(file_name).fileName()).fileName());
                    QByteArray bytes = file.readAll();
                    socket->write(make_byte_message(Command::getFile, file_name, bytes));
                    break;
                }
            }
        }
    }
}


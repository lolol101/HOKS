#include "socket_manager.h"

template<class T>
QByteArray Socket_Manager::make_byte_message(const Command &command, const QVector<T>& arguments) {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0 << quint8(command);
    for (const auto& item : arguments)
        out << item;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    return block;
}

Socket_Manager::Socket_Manager(QObject *parent) : QObject(parent) {
    socket = new QTcpSocket;
}

void Socket_Manager::connect_to_server(const QString& ip, int port) {
    socket->connectToHost(ip, port);
    connect_signals_to_slots();
}

void Socket_Manager::connect_signals_to_slots() {
    connect(socket, &QTcpSocket::readyRead, this, &Socket_Manager::slot_read_server_msg);
}

void Socket_Manager::slot_read_server_msg() {
    block_size = 0;
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_15);
    if (in.status() == QDataStream::Ok) {
        while (true) {
            if (block_size == 0) {
                if (socket->bytesAvailable() < 2)
                    break;
                in >> block_size;
            }
            if (socket->bytesAvailable() < block_size)
                break;
            block_size = 0;
            quint8 command;
            in >> command;
            switch (command) {
                case Command::checkConnection: {
                    emit got_connection(true);
                    break;
                }
                case Command::checkAuthoriziatonData: {
                    QVector<QString> args(2);
                    in >> args[0] >> args[1];
                    emit got_authorization_data_check(args);
                    break;
                }
                case Command::checkRegistrationData: {
                    QVector<QString> args(5);
                    for (int i = 0; i < 5; ++i)
                        in >> args[i];
                    emit got_registration_data_check(args);
                    break;
                }
                case Command::getRooms: {
                    QVector<QPair<int, QString>> rooms_data;
                    QPair<QString, QString> item;
                    while (!in.atEnd()) {
                        in >> item;
                        rooms_data.push_back(QPair(item.first.toInt(), item.second));
                    }
                    emit got_rooms_data(rooms_data);
                    break;
                }
                case Command::otherUserMessage: {
                    QString message, id, author, media_flag;
                    in >> message >> id >> author >> media_flag;
                    emit got_other_user_msg(QVector<QString>{message, id, author, media_flag});
                    break;
                }
                case Command::getAllUsers: {
                    QVector<QString> users_names;
                    QString size;
                    QString item;
                    in >> size;
                    for (int i = 0; i < size.toInt(); ++i) {
                        in >> item;
                        users_names.push_back(item);
                    }
                    emit got_all_user_names(users_names);
                    break;
                }
                case Command::roomCreated: {
                    QString room_name, id;
                    in >> room_name >> id;
                    emit room_created(room_name, id.toInt());
                    break;
                }
                case Command::loadMsgs: {
                    QVector<msg> msgs;
                    QVector<QString>item;
                    in >> item;
                    int room_id = item[0].toInt();
                    while (!in.atEnd()) {
                        in >> item;
                        msgs.push_back(msg(item[0], item[1], item[2], item[3].toInt()));
                    }
                    emit got_msgs(room_id, msgs);
                    break;
                }
            }
        }
    }
}

void Socket_Manager::slot_check_authorization_data(const QVector<QString> &args) {
    socket->write(make_byte_message(Command::checkAuthoriziatonData, args));
}

void Socket_Manager::slot_check_registration_data(const QVector<QString> &args) {
    socket->write(make_byte_message(Command::checkRegistrationData, args));
}

void Socket_Manager::slot_registrate_user(const QVector<QString> &args) {
    socket->write(make_byte_message(Command::registrateUser, args));
}

void Socket_Manager::slot_get_rooms_data(const QString& user_name) {
    socket->write(make_byte_message(Command::getRooms, QVector<QString>{user_name}));
}

void Socket_Manager::slot_user_msg_sent(const QVector<QString> &args) {
    socket->write(make_byte_message(Command::appendMessage, args));
}

void Socket_Manager::slot_create_new_room(const QList<QString> &people, const QString &room_name) {
    QVector<QString> args = {room_name};
    args += people.toVector();
    socket->write(make_byte_message(Command::appendRoom, args));
}

 void Socket_Manager::slot_get_all_users() {
    socket->write(make_byte_message(Command::getAllUsers, QVector<int>{}));
 }

 void Socket_Manager::slot_load_msgs(const int& room_id) {
    socket->write(make_byte_message(Command::loadMsgs, QVector<int>{room_id}));
 }

 void Socket_Manager::slot_user_enter_app(const QString& user_name) {
    socket->write(make_byte_message(Command::userEnterApp, QVector<QString>{user_name}));
 }

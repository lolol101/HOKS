#include "server.h"

QByteArray Server::make_byte_message(const Command &command, const QString& message){
    QByteArray block;
   QDataStream out(&block, QIODevice::WriteOnly);
   out << (quint16)0 << quint8(command) << message;
   out.device()->seek(0);
   out << (quint16)(block.size() - sizeof(quint16));
   return block;
}

Server::Server() : data_base("QPSQL", "127.0.0.1", "database_qt", "postgres", "postgres") {}

void Server::start() {
    if (this->listen(QHostAddress("0.0.0.0"), 1101)) {
        std::cout << "Start\n";
        connect(this, &QTcpServer::newConnection, this, &Server::new_connection);
    }
    else
        std::cout << "Error\n";
}

void Server::new_connection() {
    QTcpSocket* socket = this->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, this, &Server::slot_ready_read);
    clients.emplace_back(socket);
    socket->write(make_byte_message(Command::checkConnection, "1"));
}


void Server::slot_ready_read() {
    QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_15);
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
            QString str;
            in >> command >> str;
            switch (command) {
                case Command::checkLogin: {
                    if (data_base.check_user_in_bd(str)) {
                        socket->write(make_byte_message(checkLogin, "1"));
                    } else {
                        socket->write(make_byte_message(checkLogin, "0"));
                    }
                    break;
                }
                case Command::checkPassword: {
                    QString name = str.split(' ')[0];
                    QString password = str.split(' ')[1];
                    if (data_base.check_pass_by_username(name, password)) {
                        socket->write(make_byte_message(checkPassword, "1"));
                    } else {
                        socket->write(make_byte_message(checkPassword, "0"));
                    }
                    break;
                }
                case Command::accountRegisration: {
                    QStringList registrationData = str.split(' ');
                    data_base.registration(registrationData[0], registrationData[1], registrationData[2], registrationData[3], registrationData[4]);
                    break;
                }
            }
        }
    }
}


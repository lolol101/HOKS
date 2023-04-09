#include "server.h"

bool check_reg_exp(const QRegExp& re, const QString& str) {
    return (re.exactMatch(str));
}

template<class T>
QByteArray Server::make_byte_message(const Command &command, const std::vector<T>& arguments) {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0 << quint8(command);
    for (const auto& item : arguments)
        out << item;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    return block;
}

Server::Server() : data_base("QPSQL", "127.0.0.1", "database_qt", "postgres", "postgres") {}

void Server::start() {
    if (this->listen(QHostAddress("0.0.0.0"), 1101)) {
        qDebug() << "Start\n";
        connect(this, &QTcpServer::newConnection, this, &Server::new_connection);
    }
    else
        qDebug() << "Error\n";
}

void Server::new_connection() {
    QTcpSocket* socket = this->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, this, &Server::slot_ready_read);
    socket->write(make_byte_message(Command::checkConnection, std::vector<int>{}));
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
            in >> command;
            switch (command) {
                case Command::checkAuthoriziatonData: {
                    QString login, password;
                    in >> login >> password;
                    std::vector<QString> args(2);
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
                    std::vector<QString> errors;

                    if(!check_reg_exp(QRegExp("[A-Za-z0-9]+"), login))
                        login_error = "Некорректный формат логина";
                    if(!check_reg_exp(QRegExp("[A-Za-z0-9]+"), password))
                        password_error = "Некорректный формат пароля";
                    if(!check_reg_exp(QRegExp("[A-Za-z0-9]+@[a-z]+.com"), email))
                        email_error = "Некорректный формат email";
                    if(!check_reg_exp(QRegExp("[A-Z]{1, 1}[a-z]+"), first_name))
                        first_name_error = "Некорректное имя";
                    if(!check_reg_exp(QRegExp("[A-Z]{1, 1}[a-z]+"), last_name))
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
            }
        }
    }
}


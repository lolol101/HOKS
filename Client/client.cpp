#include "client.h"

QByteArray Client::make_byte_message(const Command &command, const QString& message) {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0 << quint8(command) << message;
    return block;
}

Client::Client(QObject *parent) : QObject(parent) {
    socket = new QTcpSocket;
    block_size = 0;
}

void Client::start() {
    socket->connectToHost("0.0.0.0", 1101);
    authWindow.show();
}

void Client::connect_signals_to_slots() {
    connect(socket, &QTcpSocket::readyRead, this, &Client::slot_ready_read);
    connect(&authWindow, &authorizationWindow::user_authorization_signal, this, &Client::slot_user_authorization);
    connect(&authWindow, &authorizationWindow::user_registration_signal, this, &Client::slot_user_registration);
    // TODO more options
}

void Client::slot_ready_read() {
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
            QString str;
            in >> command >> str;
            switch (command) {
                case Command::checkConnection: {
                    authWindow.show_authorization();
                    break;
                }
                case Command::checkLogin: {
                    if (str.toInt() == 0) {
                        authWindow.show_login_input_error("Пользователь не найден");
                        authWindow.show_registration();
                    }
                    break;
                }
                case Command::checkPassword: {
                    if (str.toInt() == 1) {
                        authWindow.show_password_input_error("Неправильный пароль");
                    } else {
                        authWindow.hide_authorization();
                        authWindow.show_main_window();
                    }
                    break;
                }
            }
        }
    }
}

void Client::slot_user_authorization(const QString &user_login, const QString &user_password) {
    socket->write(make_byte_message(checkLogin, user_login));
    socket->write(make_byte_message(checkLogin, user_login + ' ' + user_password));
}

void Client::slot_user_registration(const QString& user_login,
                                    const QString& user_password,
                                    const QString& user_email,
                                    const QString& user_first_name,
                                    const QString& user_last_name) {
    bool flag = false;
    authWindow.recover_registration_window_view();
    if (user_login.contains(' ') || user_login == "") {
       authWindow.show_login_input_error("Некорректный логин");
       flag = true;
    } if (user_password.contains(' ') || user_password.size() < 8) {
        authWindow.show_password_input_error("Неверный формат пароля");
        flag = true;
    } if (user_email.contains(' ') || user_email == "") {
        authWindow.show_email_input_error("Неверный формат email");
        flag = true;
    } if (user_first_name.contains(' ') || user_first_name == "") {
        authWindow.show_first_name_input_error("Некорректный формат фамилии");
        flag = true;
    } if (user_last_name.contains(' ') || user_last_name == "") {
        authWindow.show_last_name_input_error("Некорректный формат имени");
        flag = true;
    }
    if (!flag)
        socket->write(make_byte_message(Command::accountRegisration, user_login + ' '
                                                                    + user_password + ' '
                                                                    + user_email + ' '
                                                                    + user_first_name + ' '
                                                                    + user_last_name));
}

void Client::slot_user_main_window() {

}

void Client::slot_user_room() {

}

void Client::slot_user_print_msg() {

}

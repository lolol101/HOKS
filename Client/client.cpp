#include "client.h"

template<class T>
QByteArray Client::make_byte_message(const Command &command, const std::vector<T>& arguments) {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0 << quint8(command);
    for (const auto& item : arguments)
        out << item;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    return block;
}

void Client::show_main_window() {
    socket->write(make_byte_message(Command::getRooms, std::vector<int>{}));
    auth_window.hide_authorization();
    main_window.show_main_window();
    for (const auto& item : rooms) {
        main_window.show_room_icon(*item.second);
    }
}

Client::Client(QObject *parent) : QObject(parent) {
    socket = new QTcpSocket;
}

void Client::start() {
    socket->connectToHost("0.0.0.0", 1101);
}

void Client::connect_signals_to_slots() {
    connect(socket, &QTcpSocket::readyRead, this, &Client::slot_ready_read);
    connect(&auth_window, &authorizationWindow::user_authorization_signal, this, &Client::slot_user_authorization);
    connect(&auth_window, &authorizationWindow::user_registration_signal, this, &Client::slot_user_registration);
}

void Client::slot_ready_read() {
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
                    auth_window.show();
                    auth_window.show_authorization();
                    break;
                }
                case Command::checkAuthoriziatonData: {
                    std::vector<QString> args(2);
                    in >> args[0] >> args[1];
                    if (args[0] != "")
                        auth_window.show_login_input_error(args[0]);
                    if (args[1] != "")
                        auth_window.show_password_input_error(args[1]);
                    if (args == std::vector<QString>{"", ""}) {
                        auth_window.hide();
                        show_main_window();
                    } else
                        auth_window.show_registration();
                    break;
                }
                case Command::checkRegistrationData: {
                    std::vector<QString> args(5);
                    for (int i = 0; i < 5; ++i)
                        in >> args[i];
                    if (args[0] != "")
                        auth_window.show_login_input_error(args[0]);
                    if (args[1] != "")
                        auth_window.show_password_input_error(args[1]);
                    if (args[2] != "")
                        auth_window.show_email_input_error(args[2]);
                    if (args[3] != "")
                        auth_window.show_first_name_input_error(args[3]);
                    if (args[4] != "")
                        auth_window.show_last_name_input_error(args[4]);
                    if (args == std::vector<QString>{"", "", "", "", ""}) {
                        auth_window.hide();
                        show_main_window();
                        socket->write(make_byte_message(Command::registrateUser, args));
                    }
                    break;
                }
                case Command::getRooms: {
                    int size;
                    in >> size;
                    std::pair<int, QString> item;
                    for (int i = 0; i < size; ++i) {
                        in >> item.first >> item.second;
                        rooms.insert({item.first, std::make_unique<Room>(new Room(item.second))});
                    }
                    break;
                }
            }
        }
    }
}

void Client::slot_user_authorization(const QString &user_login, const QString &user_password) {
    socket->write(make_byte_message(Command::checkAuthoriziatonData, std::vector<QString>{user_login, user_password}));
    m_user_login = user_login;
}

void Client::slot_user_registration(const QString& user_login, const QString& user_password, const QString& user_email, const QString& user_first_name, const QString& user_last_name) {
    std::vector<QString> args = {user_login, user_password, user_email, user_first_name, user_last_name};
    auth_window.recover_registration_window_view();
    socket->write(make_byte_message(Command::checkRegistrationData, args));
}


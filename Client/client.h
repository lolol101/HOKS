#ifndef CLIENT_H
#define CLIENT_H

#include <Graphics/authorizationWindow.h>
#include <Graphics/MainWindow.h>
#include <Graphics/Room.h>
#include <Graphics/RoomIconWidget.h>
#include <Graphics/RoomInsideWidget.h>
#include <QByteArray>
#include <QTcpSocket>
#include <unordered_map>
#include "Commands.h"

class Client : public QObject {
    Q_OBJECT

private:
    QString m_user_login;

    authorizationWindow auth_window;
    MainWindow main_window;

    QTcpSocket* socket;
    quint16 block_size{0};

    std::unordered_map<int, std::unique_ptr<Room>> rooms;

    template<class T>
    QByteArray make_byte_message(const Command &command, const std::vector<T>& arguments);

    void show_main_window();
    void init_rooms();

public:
    Client(QObject *parent = nullptr);
    void start();
    void connect_signals_to_slots();

public slots:
    void slot_ready_read();
    void slot_user_authorization(const QString &user_login, const QString &user_password);
    void slot_user_registration(const QString& user_login, const QString& user_password, const QString& user_email, const QString& user_first_name, const QString& user_last_name);
//    void slotDisconnected();
};
#endif // CLIENT_H

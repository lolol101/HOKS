#ifndef CLIENT_H
#define CLIENT_H

#include <Graphics/authorizationWindow.h>
#include <QByteArray>
#include <QTcpSocket>
#include <unordered_map>
#include "Commands.h"

class Client : public QObject {
    Q_OBJECT

private:
    authorizationWindow authWindow;
    QTcpSocket* socket;
    quint16 block_size;
    QByteArray make_byte_message(const Command &command, const QString& message);

public:
    Client(QObject *parent = nullptr);
    void start();
    void connect_signals_to_slots();

public slots:
    void slot_ready_read();
    void slot_user_authorization(const QString &user_login, const QString &user_password);
    void slot_user_registration(const QString& user_login, const QString& user_password, const QString& user_email, const QString& user_first_name, const QString& user_last_name);
    void slot_user_main_window();
    void slot_user_room();
    void slot_user_print_msg();
//    void slotDisconnected();
};
#endif // CLIENT_H

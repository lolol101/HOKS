#ifndef SOCKET_MANAGER_H
#define SOCKET_MANAGER_H

#include <QByteArray>
#include <QTcpSocket>
#include <QDataStream>
#include <QFile>
#include <QFileInfo>
#include "msg.h"
#include "Commands.h"

class Socket_Manager : public QObject {
    Q_OBJECT

private:
    QTcpSocket* socket;
    quint64 block_size{0};

    template<class T>
    QByteArray make_byte_message(const Command &command, const QVector<T>& arguments);
    QByteArray make_byte_message(const Command &command, const QString& file_name, const QByteArray& bytes);
public:
    Socket_Manager(QObject *parent = nullptr);

    void connect_to_server(const QString& ip, int port);
    void connect_signals_to_slots();

signals:
    void got_connection(bool flag);
    void got_authorization_data_check(const QVector<QString>& args);
    void got_registration_data_check(const QVector<QString>& args);
    void got_rooms_data(const QVector<QPair<int, QString>>& rooms);
    void got_other_user_msg(const QVector<QString>& args);
    void got_all_user_names(const QVector<QString>& user_names);
    void got_msgs(const int& room_id, const QVector<msg> msgs);
    void got_file(const QByteArray& bytes, const QString& filename);
    void room_created(const QString& room_name, int id);

public slots:
    void slot_get_file(const QString& file_name);
    void slot_read_server_msg();
    void slot_check_authorization_data(const QVector<QString>& args);
    void slot_check_registration_data(const QVector<QString>& args);
    void slot_registrate_user(const QVector<QString>& args);
    void slot_get_rooms_data(const QString& user_name);
    void slot_user_msg_sent(const QVector<QString>& args);
    void slot_create_new_room(const QList<QString>& people, const QString& room_name);
    void slot_get_all_users();
    void slot_load_msgs(const int& room_id);
    void slot_user_enter_app(const QString& user_name);
    void slot_file_send(const QString& file_name, const QByteArray& bytes, const QVector<QString>& args);

};

#endif // SOCKET_MANAGER_H

#ifndef CLIENT_H
#define CLIENT_H

#include <QMap>
#include <QPointer>
#include <Graphics/authorizationWindow.h>
#include <Graphics/MainWindow.h>
#include <Graphics/Room.h>
#include <Graphics/RoomIconWidget.h>
#include <Graphics/RoomInsideWidget.h>
#include <Graphics/MessageWidget.h>
#include <socket_manager.h>

class Client : public QObject {
    Q_OBJECT

private:
    QString m_user_login;
    QString m_password;
    QString m_email;
    QString m_first_name;
    QString m_last_name;

    authorizationWindow auth_window;
    MainWindow main_window;
    Socket_Manager s_manager;

    QMap<int, bool> room_open_flags;
    QMap<int, QPointer<Room>> rooms;
    QVector<QString> all_user_names;

    template<class T>
    QByteArray make_byte_message(const Command &command, const QVector<T>& arguments);

public:
    Client(QObject *parent = nullptr);
    void start();
    void connect_signals_to_slots();

signals:
    void authorization_check(const QVector<QString>& args);
    void registration_check(const QVector<QString>& args);
    void registrate_user(const QVector<QString>& args);
    void init_rooms(const QString& user_name);
    void message_send(const QVector<QString>& args);
    void create_new_room(const QList<QString>& people, const QString& room_name);
    void get_msgs(const int& room_id);
    void get_all_users();
    void user_enter_app(const QString& user_name);

public slots:
    // graphic`s slots
    void slot_authorization_btn(const QString &user_login, const QString &user_password);
    void slot_registration_btn(const QString& user_login, const QString& user_password, const QString& user_email, const QString& user_first_name, const QString& user_last_name);
    void slot_message_send_btn(const QString& text_message);
    void slot_create_room_btn();
    void slot_finish_create_room_btn(const QList<QString>& people, const QString& room_name);

    // socket manager`s slots
    void slot_connection_check();
    void slot_authorization_data_check(const QVector<QString>& args);
    void slot_registration_data_check(const QVector<QString>& args);
    void slot_init_rooms(const QVector<QPair<int, QString>> args);
    void slot_other_user_message(const QVector<QString>& args);
    void slot_got_all_user_names(const QVector<QString>& user_names);
    void slot_room_created(const QString& room_name, const int& id);
    void slot_room_icon_clicked();
    void slot_got_msgs(const int& room_id, const QVector<msg>& msgs);

};
#endif // CLIENT_H

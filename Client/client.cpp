#include "client.h"


Client::Client(QObject *parent) : QObject(parent) {}

void Client::start() {
    connect_signals_to_slots();
    s_manager.connect_to_server("185.125.201.130", 1101);
    auth_window.show();
    auth_window.show_authorization();
}

void Client::connect_signals_to_slots() {
    connect(&auth_window, &authorizationWindow::user_authorization_signal, this, &Client::slot_authorization_btn);
    connect(&auth_window, &authorizationWindow::user_registration_signal, this, &Client::slot_registration_btn);
    connect(&main_window, &MainWindow::push_on_creating_new_room_signal, this, &Client::slot_create_room_btn);
    connect(&main_window, &MainWindow::push_on_finish_create_room_signal, this, &Client::slot_finish_create_room_btn);
    connect(&s_manager, &Socket_Manager::got_connection, this, &Client::slot_connection_check);
    connect(&s_manager, &Socket_Manager::got_authorization_data_check, this, &Client::slot_authorization_data_check);
    connect(&s_manager, &Socket_Manager::got_registration_data_check, this, &Client::slot_registration_data_check);
    connect(&s_manager, &Socket_Manager::got_rooms_data, this, &Client::slot_init_rooms);
    connect(&s_manager, &Socket_Manager::got_other_user_msg, this, &Client::slot_other_user_message);
    connect(&s_manager, &Socket_Manager::got_all_user_names, this, &Client::slot_got_all_user_names);
    connect(&s_manager, &Socket_Manager::room_created, this, &Client::slot_room_created);
    connect(&s_manager, &Socket_Manager::got_msgs, this, &Client::slot_got_msgs);
    connect(&s_manager, &Socket_Manager::got_file, this, &Client::slot_got_file);
    connect(this, &Client::authorization_check, &s_manager, &Socket_Manager::slot_check_authorization_data);
    connect(this, &Client::registration_check, &s_manager, &Socket_Manager::slot_check_registration_data);
    connect(this, &Client::init_rooms, &s_manager, &Socket_Manager::slot_get_rooms_data);
    connect(this, &Client::message_send, &s_manager, &Socket_Manager::slot_user_msg_sent);
    connect(this, &Client::registrate_user, &s_manager, &Socket_Manager::slot_registrate_user);
    connect(this, &Client::get_all_users, &s_manager, &Socket_Manager::slot_get_all_users);
    connect(this, &Client::create_new_room, &s_manager, &Socket_Manager::slot_create_new_room);
    connect(this, &Client::user_enter_app, &s_manager, &Socket_Manager::slot_user_enter_app);
    connect(this, &Client::get_msgs, &s_manager, &Socket_Manager::slot_load_msgs);
    connect(this, &Client::get_file, &s_manager, &Socket_Manager::slot_get_file);
    connect(this, &Client::file_send, &s_manager, &Socket_Manager::slot_file_send);
}

void Client::slot_connection_check() {

}

void Client::slot_authorization_btn(const QString &user_login, const QString &user_password) {
    m_user_login = user_login;
    emit authorization_check(QVector<QString>{user_login, user_password});
}

void Client::slot_authorization_data_check(const QVector<QString>& args){
    if (args[1] != "") {
        auth_window.show_password_input_error(args[1]);
        return;
    }
    if (args[0] != "") {
        auth_window.show_login_input_error(args[0]);
    }
    if (args == QVector<QString>{"", ""}) {
        emit init_rooms(m_user_login);
        auth_window.hide();
        main_window.show_main_window();
        emit user_enter_app(m_user_login);
    } else {
        auth_window.show_registration();
    }
}

void Client::slot_registration_btn(const QString& user_login, const QString& user_password, const QString& user_email, const QString& user_first_name, const QString& user_last_name) {
    m_user_login = user_login, m_password = user_password, m_email = user_email, m_first_name = user_first_name, m_last_name = user_last_name;
    emit registration_check(QVector<QString>{user_login, user_password, user_email, user_first_name, user_last_name});
}

void Client::slot_registration_data_check(const QVector<QString>& args) {
    auth_window.recover_registration_window_view();
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
    if (args == QVector<QString>{"", "", "", "", ""}) {
        emit registrate_user(QVector{m_user_login, m_password, m_email, m_first_name, m_last_name});
        emit user_enter_app(m_user_login);
        auth_window.hide();
        main_window.show_main_window();
    }
}

void Client::slot_init_rooms(const QVector<QPair<int, QString>> &args) {
    for (const auto& item : args) {
        if (item.first != 0) {
            rooms.insert(item.first, QPointer<Room>(new Room(item.second, item.first)));
            connect(rooms.last(), &Room::room_icon_pressed, this, &Client::slot_room_icon_clicked);
            connect(rooms.last(), &Room::clicked_send_button, this, &Client::slot_message_send_btn);
            connect(rooms.last(), &Room::signal_open_file_button, this, &Client::slot_file_message_btn);
            connect(rooms.last(), &Room::signal_clicked_clip_button, this, &Client::slot_file_upload_btn);
            main_window.show_room_icon(*rooms.last());
        }
    }
}

void Client::slot_message_send_btn(const QString& text_message) {
    if (!text_message.isEmpty()) {
        Room *room_sender = static_cast<Room*>(sender());
        room_sender->show_user_message(text_message, m_user_login, false);
        emit message_send(QVector<QString>{text_message, QString::number(room_sender->get_id()) , m_user_login, "0"});
    }
}

void Client::slot_other_user_message(const QVector<QString> &args) {
    rooms[args[1].toInt()]->show_other_message(args[0], args[2], static_cast<bool>(args[3].toInt()));
}

void Client::slot_create_room_btn() {
    if (!current_room.isNull())
        main_window.hide_room_inside(*current_room);
    main_window.show_creation_new_room();
    emit get_all_users();
}

void Client::slot_finish_create_room_btn(const QList<QString>& people, const QString& room_name) {
    if (!room_name.isEmpty() && !people.isEmpty()) {
        QList<QString> all_people = people;
        all_people.push_back(m_user_login);
        emit create_new_room(all_people, room_name);
        main_window.slot_hide_create_room();
    }
}

void Client::slot_file_message_btn(const QString &file_name) {
    QProcess* process = new QProcess();
    process->setWorkingDirectory("/");
    process->start(QDir::currentPath() + "/checkFileExistence.sh", {file_name});
    while(process->waitForFinished());
    if (process->exitCode() == 0) {
        QString path;
        path = process->readAll();
        path.remove(path.size() - 1, 1);
        QProcess* tmp_process = new QProcess();
        tmp_process->start(QDir::currentPath() + "/openFile.sh", {path});
        if (tmp_process->waitForFinished(500))
            delete tmp_process;
    } else {
        emit get_file(file_name);
    }
    delete process;
}

void Client::slot_file_upload_btn(const QString &file_path) {
    QFileInfo file(file_path);
    QFile file1(file_path);
    file1.open(QIODevice::ReadOnly);
    Room *room_sender = static_cast<Room*>(sender());
    room_sender->show_user_message(file.fileName(), m_user_login, true);
    emit file_send(file.fileName(), file1.readAll(), QVector<QString>{file.fileName(), QString::number(room_sender->get_id()) , m_user_login, "1"});
}

void Client::slot_got_all_user_names(const QVector<QString> &user_names) {
    all_user_names = user_names;
    main_window.show_creation_new_room();
    for (auto& item : all_user_names) {
        if (item != m_user_login)
            main_window.show_checkbox(item);
    }
}

void Client::slot_room_created(const QString& room_name, const int& id) {
    QPointer<Room> room = new Room(room_name, id);
    rooms[id] = room;
    connect(room, &Room::room_icon_pressed, this, &Client::slot_room_icon_clicked);
    connect(room, &Room::clicked_send_button, this, &Client::slot_message_send_btn);
    connect(room, &Room::signal_open_file_button, this, &Client::slot_file_message_btn);
    connect(room, &Room::signal_clicked_clip_button, this, &Client::slot_file_upload_btn);
    main_window.show_room_icon(*rooms.last());
}

void Client::slot_room_icon_clicked() {
    QPointer<Room> room_sender = static_cast<Room*>(sender());
    main_window.hide_create_room();
    current_room = room_sender;
    for (const auto& item : rooms) {
        if (item != room_sender)
            main_window.hide_room_inside(*item);
    }
    main_window.show_room_inside(*room_sender);
    emit get_msgs(room_sender->get_id());
}

void Client::slot_got_msgs(const int& room_id, const QVector<msg>& msgs) {
    main_window.show_room_inside(*rooms[room_id]);
    if (!room_open_flags[room_id]) {
        for (const auto& item : msgs) {
            QString message = item.text_message;
            if (item.media) {
                message = item.text_message.mid(9);
                if (item.author != m_user_login)
                    rooms[room_id]->show_other_message(item.text_message, item.author, true);
                else
                    rooms[room_id]->show_user_message(item.text_message, m_user_login, true);
            } else {
                if (item.author != m_user_login)
                    rooms[room_id]->show_other_message(item.text_message, item.author, false);
                else
                    rooms[room_id]->show_user_message(item.text_message, m_user_login, false);
            }
        }
    }
    room_open_flags[room_id] = true;
}

void Client::slot_got_file(const QByteArray& bytes, const QString& file_name) {
    QProcess* process = new QProcess();
    QFile file(QDir::currentPath() + "/downloadFiles/" + file_name);
    file.open(QIODevice::ReadWrite);
    file.write(bytes);
    process->start(QDir::currentPath() + "/openFile.sh", {QDir::currentPath() + "/downloadFiles/" + file_name});
    if (process->waitForFinished(500))
        delete process;
}

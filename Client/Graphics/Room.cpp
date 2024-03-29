#include "Room.h"
#include "ui_Room.h"
#include <QString>
#include <QList>

Room::Room(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Room)
{
    ui->setupUi(this);
}

int Room::get_id() {
    return m_id;
}

QString Room::get_room_name() const {
    return room_icon->room_name_;
}

void Room::show_user_message(const QString& text_message, const QString &author, bool is_media) {
    room_inside->show_message(&room_inside->append_user_message(text_message, author, is_media));
}

void Room::show_other_message(const QString& text_message, const QString &author, bool is_media) {
    room_inside->show_message(&room_inside->append_other_message(text_message, author, is_media));
}

Room::Room(const QString &room_name, const int id)  {
    m_id = id;
    room_icon = new RoomIconWidget(room_name);
    room_inside = new RoomInsideWidget();
    room_inside->hide();
    room_icon->hide();
    connect(room_icon, &RoomIconWidget::clicked_icon, this, &Room::slot_clicked_icon_room);
    connect(room_inside, &RoomInsideWidget::clicked_send_button, this, &::Room::slot_clicked_send_button);

    connect(room_inside, &RoomInsideWidget::clicked_clip_button, this, &::Room::slot_clicked_clip_button);

    connect(this->room_inside, &RoomInsideWidget::signal_open_file_button, this, &Room::slot_open_file_button);
}

void Room::slot_clicked_send_button(const QString &text_message) {
    emit clicked_send_button(text_message);
}

void Room::slot_clicked_clip_button(const QString &path) {
    if (path != "") {
        emit signal_clicked_clip_button(path);
    }
}

void Room::slot_clicked_icon_room() {
    emit room_icon_pressed();
}

void Room::set_room_name_at_top(const QString &room_name) {
    this->room_inside->set_room_name(room_name);
}

Room::~Room()
{
    delete ui;
}

void Room::slot_open_file_button(const QString &file_name, const QString &author) {
    emit signal_open_file_button(file_name, author);
}

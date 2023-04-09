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

void Room::show_user_message(const QString& text_message) {
    room_inside->show_message(&room_inside->append_user_message(text_message));
}

void Room::show_other_message(const QString& text_message) {
    room_inside->show_message(&room_inside->append_other_message(text_message));
}

Room::Room(const QString &room_name, const int& id) : m_id(id)  {
    room_icon = new RoomIconWidget(room_name);
    room_inside = new RoomInsideWidget();
    room_icon->room_icon_->hide();
    room_inside->room_inside_->hide();
    connect(this->room_inside, &RoomInsideWidget::clicked_send_button, this, &::Room::slot_clicked_send_button);
}

void Room::slot_clicked_send_button(const QString &text_message) {
    emit clicked_send_button(text_message);
}

Room::~Room()
{
    delete ui;
}

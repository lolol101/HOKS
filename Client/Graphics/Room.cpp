#include "Graphics/Room.h"
#include "ui_Room.h"
#include <QString>
#include <QList>

Room::Room(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Room)
{
    ui->setupUi(this);
}

Room::Room(const QString &room_name) {
    room_icon = new RoomIconWidget(room_name);
    room_inside = new RoomInsideWidget(room_icon);
    room_icon->room_icon_->hide();
    room_inside->room_inside_->hide();
}

Room::~Room()
{
    delete ui;
}

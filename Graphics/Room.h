#ifndef ROOM_H
#define ROOM_H

#include <QWidget>
#include <QString>
#include <RoomIconWidget.h>
#include <RoomInsideWidget.h>

namespace Ui {
class Room;
}

class Room : public QWidget
{
    Q_OBJECT

public:
    explicit Room(QWidget *parent = nullptr);

    explicit Room(const QString &room_name) {
        room_icon = new RoomIconWidget(room_name);
        room_inside = new RoomInsideWidget(room_icon);
        room_icon->room_icon_->hide();
        room_inside->room_inside_->hide();
    }

    RoomIconWidget *room_icon;
    RoomInsideWidget *room_inside;

    ~Room();

private:
    Ui::Room *ui;
signals:
    void room_icon_pressed();

};

#endif // ROOM_H

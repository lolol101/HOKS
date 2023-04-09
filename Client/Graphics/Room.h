#ifndef ROOM_H
#define ROOM_H

#include <QWidget>
#include <QString>
#include <QList>
#include <Graphics/RoomIconWidget.h>
#include <Graphics/RoomInsideWidget.h>

namespace Ui {
class Room;
}

class Room : public QWidget
{
    Q_OBJECT

public:
    explicit Room(QWidget *parent = nullptr);

    explicit Room(const QString &room_name);

    RoomIconWidget *room_icon;
    RoomInsideWidget *room_inside;

    ~Room();

private:
    Ui::Room *ui;
signals:
    void room_icon_pressed();

};

#endif // ROOM_H

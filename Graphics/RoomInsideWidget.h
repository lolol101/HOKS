#ifndef ROOMINSIDEWIDGET_H
#define ROOMINSIDEWIDGET_H

#include <QWidget>
#include <RoomIconWidget.h>

namespace Ui {
class RoomInsideWidget;
}

class RoomInsideWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RoomInsideWidget(QWidget *parent = nullptr);

    RoomInsideWidget(const RoomIconWidget *room_icon) {
        room_inside_ = new QWidget(this);
    }

    QWidget *room_inside_;

    ~RoomInsideWidget();

private:
    Ui::RoomInsideWidget *ui;
};

#endif // ROOMINSIDEWIDGET_H

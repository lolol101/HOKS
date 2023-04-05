#ifndef ROOMICONWIDGET_H
#define ROOMICONWIDGET_H

#include <QWidget>
#include <QString>
#include <QPushButton>

namespace Ui {
class RoomIconWidget;
}

class RoomIconWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RoomIconWidget(QWidget *parent = nullptr);

    RoomIconWidget(const QString &room_name) {
        room_name_ = room_name;
        room_icon_ = new QPushButton(this);
        room_icon_->setText(room_name);
    }

    QString room_name_;
    QPushButton *room_icon_;

    ~RoomIconWidget();

private:
    Ui::RoomIconWidget *ui;
};

#endif // ROOMICONWIDGET_H

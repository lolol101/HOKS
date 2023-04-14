#ifndef ROOMICONWIDGET_H
#define ROOMICONWIDGET_H

#include <QWidget>
#include <QString>
#include <QPushButton>
#include <appstyle.h>

namespace Ui {
class RoomIconWidget;
}

class RoomIconWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RoomIconWidget(QWidget *parent = nullptr);

    RoomIconWidget(const QString &room_name);

    QString room_name_;
    QPushButton *room_icon_;
    style_table current_style;

    ~RoomIconWidget();

signals:
    void clicked_icon();

public slots:
    void slot_clicked();

private:
    Ui::RoomIconWidget *ui;
};

#endif // ROOMICONWIDGET_H

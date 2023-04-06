#ifndef ROOMINSIDEWIDGET_H
#define ROOMINSIDEWIDGET_H

#include <QWidget>
#include <QString>
#include <RoomIconWidget.h>
#include <QTextEdit>
#include "appstyle.h"
#include <QList>

namespace Ui {
class RoomInsideWidget;
}

class RoomInsideWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RoomInsideWidget(QWidget *parent = nullptr);

    RoomInsideWidget(const RoomIconWidget *room_icon, QList<QString> *room_messages);

    style_table current_style;

    QWidget *room_inside_;
    QList<QString> *room_messages_;

    QTextEdit *message_line;

    ~RoomInsideWidget();

private:
    Ui::RoomInsideWidget *ui;
};

#endif // ROOMINSIDEWIDGET_H

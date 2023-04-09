#ifndef ROOMINSIDEWIDGET_H
#define ROOMINSIDEWIDGET_H

#include <QWidget>
#include <QString>
#include <Graphics/RoomIconWidget.h>
#include <QTextEdit>
#include "appstyle.h"
#include <QList>
#include <QScrollArea>
#include <Graphics/MessageWidget.h>

namespace Ui {
class RoomInsideWidget;
}

class RoomInsideWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RoomInsideWidget(QWidget *parent = nullptr);

    RoomInsideWidget();

    style_table current_style;

    QWidget *room_inside_;

    QTextEdit *message_line;

    QWidget *inside_messages_widget;
    QScrollArea *inside_messages_scroll_area;

    QWidget *inside_room_name;

    MessageWidget& append_user_message(const QString &message_text);
    MessageWidget& append_other_message(const QString &message_text);

    void show_message(MessageWidget *message_widget);

    int index = 0;

    ~RoomInsideWidget();

private:
    Ui::RoomInsideWidget *ui;
};

#endif // ROOMINSIDEWIDGET_H

#ifndef ROOMINSIDEWIDGET_H
#define ROOMINSIDEWIDGET_H

#include <QWidget>
#include <QString>
#include <RoomIconWidget.h>
#include <QTextEdit>
#include "appstyle.h"
#include <QList>
#include <QScrollArea>
#include <MessageWidget.h>
#include <QPushButton>
#include <QLabel>

namespace Ui {
class RoomInsideWidget;
}

class RoomInsideWidget : public QWidget
{
    Q_OBJECT

public:
    RoomInsideWidget();

    style_table current_style;

    QWidget *room_inside_;

    QTextEdit *message_line;

    QString get_message_line();

    QWidget *inside_messages_widget;
    QScrollArea *inside_messages_scroll_area;

    QWidget *inside_room_name;

    QLabel *inside_room_name_label;

    QPushButton *send_message_button;

    MessageWidget& append_user_message(const QString &message_text);
    MessageWidget& append_other_message(const QString &message_text);

    void show_message(MessageWidget *message_widget);

    void set_room_name(const QString &room_name);

    int index = 0;

    ~RoomInsideWidget();

signals:
    void clicked_send_button(const QString& text_message);

private slots:
    void slot_clicked_send_button(const QString& text_message);

private:
    Ui::RoomInsideWidget *ui;
};

#endif // ROOMINSIDEWIDGET_H

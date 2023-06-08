#ifndef ROOMINSIDEWIDGET_H
#define ROOMINSIDEWIDGET_H

#include <QWidget>
#include <QString>
#include <Graphics/RoomIconWidget.h>
#include <QTextEdit>
#include "Graphics/appstyle.h"
#include <QList>
#include <QScrollArea>
#include <Graphics/MessageWidget.h>
#include <QPushButton>
#include <QLabel>
#include <Graphics/MessageLine.h>
#include <QFileDialog>

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

    MessageLine *message_line;

    QWidget *message_line_area_widget;

    QWidget *inside_messages_widget;

    QScrollArea *inside_messages_scroll_area;

    QWidget *inside_room_name_widget;

    QLabel *inside_room_name_label;

    QString get_message_line();

    QPushButton *send_message_button;

    QPushButton *clip_button;

    MessageWidget& append_user_message(const QString &message_text, const QString &author, bool is_media);
    MessageWidget& append_other_message(const QString &message_text, const QString &author, bool is_media);

    void show_message(MessageWidget *message_widget);

    void set_room_name(const QString &room_name);

    int index = 0;

    ~RoomInsideWidget();

signals:
    void clicked_send_button(const QString& text_message);
    void clicked_clip_button(const QString &path);
    void signal_open_file_button(const QString &file_name, const QString &author);

private slots:
    void slot_clicked_send_button();
    void slot_clicked_clip_button();
    void slot_open_file_button(const MessageWidget& sender_);

private:
    Ui::RoomInsideWidget *ui;
};

#endif // ROOMINSIDEWIDGET_H

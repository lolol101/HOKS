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

    explicit Room(const QString &room_name, const int id);

    RoomIconWidget *room_icon;
    RoomInsideWidget *room_inside;

    int get_id();
    QString get_room_name() const;

    void show_user_message(const QString& text_message, const QString &author, bool is_media);
    void show_other_message(const QString& text_message, const QString &author, bool is_media);

    void set_room_name_at_top(const QString &room_name);

    bool first_use = true;

    ~Room();

private:
    Ui::Room *ui;
    int m_id;

private slots:
    void slot_clicked_send_button(const QString& text_message);
    void slot_clicked_icon_room();
    void slot_clicked_clip_button(const QString& path);

    void slot_open_file_button(const QString &file_name, const QString &author);

signals:
    void clicked_send_button(const QString& text_message);
    void signal_clicked_clip_button(const QString& path);
    void room_icon_pressed();
    void clicked_send_button_signal(const QString &file_name, const QString &author);

    void signal_open_file_button(const QString &file_name, const QString &author);
};

#endif // ROOM_H

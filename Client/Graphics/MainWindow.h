#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Graphics/appstyle.h>
#include <QScrollArea>
#include <Graphics/RoomIconWidget.h>
#include <Graphics/RoomInsideWidget.h>
#include <Graphics/Room.h>
#include <Graphics/appstyle.h>
#include <QLineEdit>
#include <Graphics/NewRoomWidget.h>
#include <QColor>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    QWidget *rooms_widget;
    QScrollArea *scroll_rooms_widget;

    style_table current_style;

    void make_window_skillet();
    void show_main_window();

    void show_room_icon(const Room &room_icon);
    void show_room_inside(Room &room_inside);
    void hide_room_inside(Room &room_inside);
    void hide_room_icon(Room &room_inside);

    void set_standard_line_edit_placeholder_color(QLineEdit *line_edit);
    void set_standard_line_edit_placeholder_color(QTextEdit *line_edit);

    const int width_rooms_area = 250;
    const int delta = 2;

    int index = 0;

    QWidget *top_widget;

    QLineEdit *search_line_edit;

    QPushButton *creating_new_room_button;

    NewRoomWidget& make_creation_new_room();

    QString get_search_line_edit();

    void draw_creation_new_room(NewRoomWidget* new_room_widget);

    void show_creation_new_room();

    NewRoomWidget *new_room;

    ~MainWindow();

public slots:
    void slot_open_main_window();
    void push_on_creating_new_room_slot();
    void push_on_finish_create_room_slot(const QList<QString>& peoples, const QString& room_name);
    void show_checkbox(const QString &chechbox_name);
    void slot_hide_create_room();

signals:
    void hide_create_room();
    void push_on_creating_new_room_signal();
    void push_on_finish_create_room_signal(const QList<QString>& peoples, const QString& room_name);
    void show_checkbox_signal(const QString &chechbox_name);


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

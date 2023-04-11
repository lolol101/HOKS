#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <appstyle.h>
#include <QScrollArea>
#include <RoomIconWidget.h>
#include <RoomInsideWidget.h>
#include <Room.h>
#include <appstyle.h>
#include <QLineEdit>
#include <NewRoomWidget.h>

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

    const int width_rooms_area = 250;
    const int delta = 2;

    int index = 0;

    QWidget *top_widget;

    QLineEdit *search_line_edit;

    QPushButton *creating_new_room_button;

    NewRoomWidget& make_creation_new_room();

    QString get_search_line_edit();

    void show_creation_new_room(NewRoomWidget* new_room_widget);

    ~MainWindow();

public slots:
    void slot_open_main_window();
    void push_on_creating_new_room_slot();

signals:
    void push_on_creating_new_room_signal();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

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
    QScrollArea *scrollArea;

    style_table current_style;

    void make_window_skillet();
    void show_main_window();

    void show_room_icon(const Room &room_icon);
    void show_room_inside(const Room &room_inside);

    const int width_rooms_area = 250;
    const int delta = 2;

    int index = 0;

    QWidget *top_widget;

    QLineEdit *search_line_edit;

    QPushButton *creating_new_room_button;

    NewRoomWidget& make_creation_new_room();

    void show_creation_new_room(NewRoomWidget* new_room_widget);

    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <appstyle.h>
#include <QScrollArea>
#include <RoomIconWidget.h>
#include <RoomInsideWidget.h>
#include <Room.h>
#include <appstyle.h>

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

    void show_room_icon(const Room &room_icon, int y);
    void show_room_inside(const Room &room_inside);

    const int width_rooms_area = 250;
    const int delta = 2;

    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
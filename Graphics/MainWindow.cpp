#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <RoomIconWidget.h>
#include <QScrollArea>
#include <Room.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    make_window_skillet();
    Room *r = new Room("123");
    show_room_icon(*r, 2);
    show_room_inside(*r);
    r->deleteLater();
}

void MainWindow::show_main_window() {
    MainWindow* m;
    m = new MainWindow();
    m->show();
}

void MainWindow::make_window_skillet() {
    this->move(170, 20);
    this->setFixedSize(1000, 700);

    QString default_style = current_style.button_standard +
            current_style.main_window +
            current_style.line_edit_standard +
            current_style.label_standard +
            current_style.message_box_standard;
    qApp->setStyleSheet(default_style);
    ui->setupUi(this);

    rooms_widget = new QWidget();
    rooms_widget->setFixedSize(300, 698);
    scrollArea = new QScrollArea(this);
    scrollArea->setWidget(rooms_widget);
    scrollArea->setMinimumSize(310, 700);
}

void MainWindow::show_room_icon(const Room &room, int index) {
    room.room_icon->room_icon_->setParent(rooms_widget);
    room.room_icon->room_icon_->move(20, index * 50 + 20);
    room.room_icon->room_icon_->show();
}

void MainWindow::show_room_inside(const Room &room) {
    room.room_inside->room_inside_->setParent(this);
    room.room_inside->room_inside_->setStyleSheet("background-color: #666666;");
    room.room_inside->room_inside_->move(310, 0);
    room.room_inside->room_inside_->setFixedSize(690, 700);
    room.room_inside->room_inside_->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}


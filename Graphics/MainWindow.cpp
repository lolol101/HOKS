#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <RoomIconWidget.h>
#include <QScrollArea>
#include <Room.h>
#include <MessageWidget.h>
#include <RoomInsideWidget.h>
#include <QCheckBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    make_window_skillet();

//    for (int i = 0; i < 20; ++i) {
//        Room *r = new Room("Комната друзей");
//        show_room_icon(*r);
//        show_room_inside(*r);
//        for (int j = 0; j < 10; j += 2) {
//            MessageWidget& msg1 = r->room_inside->append_user_message("Hello, my friend!");
//            MessageWidget& msg2 = r->room_inside->append_other_message("Hi!");
//            r->room_inside->show_message(&msg1);
//            r->room_inside->show_message(&msg2);
//            }
//        }
    NewRoomWidget& new_room = make_creation_new_room();
    show_creation_new_room(&new_room);
    new_room.select_users_widget->setFixedHeight(1000);
    for (int i = 0; i < 100; ++i) {
        QWidget &chb1 = new_room.make_checkbox_for_person("Ilia");
        new_room.show_checkbox_for_person(&chb1);
    }
    new_room.deleteLater();
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
    rooms_widget->setFixedSize(width_rooms_area, this->height());
    scrollArea = new QScrollArea(this);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setWidget(rooms_widget);
    scrollArea->setStyleSheet(current_style.rooms_space_scroll_bar);
    rooms_widget->setStyleSheet(current_style.rooms_space_widget);
    scrollArea->setMinimumSize(width_rooms_area + delta, this->height());
    scrollArea->show();
}

void MainWindow::show_room_icon(const Room &room) {
    int room_icon_height = room.room_icon->room_icon_->height();
    int height = index * room_icon_height + delta;
    ++index;
    room.room_icon->room_icon_->setParent(rooms_widget);
    room.room_icon->room_icon_->move(delta, height);
    room.room_icon->room_icon_->show();
    if (height >= this->height()) {
        rooms_widget->setFixedHeight(height + room_icon_height + delta);
    }
}

void MainWindow::show_room_inside(const Room &room) {
    room.room_inside->room_inside_->setParent(this);
    room.room_inside->room_inside_->move(width_rooms_area + delta, 0);
    room.room_inside->room_inside_->setFixedSize(this->width() - width_rooms_area - delta, this->height());
    room.room_inside->room_inside_->show();

    room.room_inside->inside_room_name->move(1, 0);
    room.room_inside->inside_room_name->setFixedSize(room.room_inside->room_inside_->width(), 50);
    room.room_inside->inside_room_name->setStyleSheet(current_style.inside_room_name_widget);
    room.room_inside->inside_room_name->show();

    room.room_inside->message_line->setFixedSize(700, 46);
    room.room_inside->message_line->move(1, room.room_inside->room_inside_->height() - room.room_inside->message_line->height());
    room.room_inside->message_line->setStyleSheet(current_style.inside_message_line);

    room.room_inside->inside_messages_widget->setStyleSheet(current_style.inside_messages_widget);

    room.room_inside->inside_messages_widget->setFixedSize(room.room_inside->room_inside_->width() - 2,
                                                           room.room_inside->room_inside_->height() -
                                                           room.room_inside->message_line->height() -
                                                           room.room_inside->inside_room_name->height() - 2);

    room.room_inside->inside_messages_scroll_area->move(0, room.room_inside->inside_room_name->height());
    room.room_inside->inside_messages_scroll_area->setFixedSize(room.room_inside->room_inside_->width(),
                                                                room.room_inside->room_inside_->height() -
                                                                room.room_inside->message_line->height() -
                                                                room.room_inside->inside_room_name->height());
    room.room_inside->inside_messages_scroll_area->setWidget(room.room_inside->inside_messages_widget);
    room.room_inside->inside_messages_scroll_area->setStyleSheet(current_style.inside_messages_widget);

    room.room_inside->send_message_button->setGeometry(room.room_inside->room_inside_->width() - 39, room.room_inside->room_inside_->height() - 39, 32, 32);
    room.room_inside->send_message_button->setStyleSheet(current_style.send_message_button);

    room.room_inside->inside_messages_scroll_area->setStyleSheet("");
}

NewRoomWidget& MainWindow::make_creation_new_room() {
    NewRoomWidget *new_room_widget = new NewRoomWidget();
    return *new_room_widget;
}

void MainWindow::show_creation_new_room(NewRoomWidget* new_room_widget) {
    new_room_widget->create_new_room_widget->setParent(this);
    new_room_widget->select_users_scroll_area->setParent(new_room_widget->create_new_room_widget);

    new_room_widget->create_new_room_widget->setFixedSize(this->width() - width_rooms_area - delta, this->height());
    new_room_widget->create_new_room_widget->move(width_rooms_area + delta, 0);
    new_room_widget->create_new_room_widget->show();

    new_room_widget->new_room_name_line_edit->move(270, 0);
    new_room_widget->new_room_name_line_edit->setFixedSize(470, 38);
    new_room_widget->new_room_name_line_edit->setStyleSheet(current_style.line_edit_standard);
    new_room_widget->new_room_name_line_edit->show();

    new_room_widget->users_search_line_edit->move(0, 650);
    new_room_widget->users_search_line_edit->setFixedSize(470, 38);
    new_room_widget->users_search_line_edit->setStyleSheet(current_style.line_edit_standard);
    new_room_widget->users_search_line_edit->show();

    new_room_widget->room_name_label->move(60, 8);
    new_room_widget->room_name_label->setStyleSheet("font-size: 20px;");
    new_room_widget->room_name_label->show();

    new_room_widget->select_users_widget->setFixedSize(746, 610);
    new_room_widget->select_users_widget->setStyleSheet(current_style.select_people_widget);

    new_room_widget->select_users_scroll_area->setWidget(new_room_widget->select_users_widget);
    new_room_widget->select_users_scroll_area->move(0, new_room_widget->new_room_name_line_edit->height());
    new_room_widget->select_users_scroll_area->setFixedSize(748, 610);
    new_room_widget->select_users_scroll_area->setStyleSheet("");

    new_room_widget->cancel_create_new_room_button->move(485, 650);
    new_room_widget->cancel_create_new_room_button->setStyleSheet(current_style.button_standard);
    new_room_widget->cancel_create_new_room_button->show();

    new_room_widget->create_new_room_button->move(618, 650);
    new_room_widget->create_new_room_button->setStyleSheet(current_style.button_standard);
    new_room_widget->create_new_room_button->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}


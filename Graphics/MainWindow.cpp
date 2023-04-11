#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <RoomIconWidget.h>
#include <QScrollArea>
#include <Room.h>
#include <MessageWidget.h>
#include <RoomInsideWidget.h>
#include <QCheckBox>
#include <QSize>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    make_window_skillet();

//    for (int i = 0; i < 20; ++i) {
//        Room *r = new Room("Комната друзей", 123);
//        show_room_icon(*r);
//        show_room_inside(*r);
//        for (int j = 0; j < 1; ++j) {
//            MessageWidget& msg1 = r->room_inside->append_user_message("Привет! Привет! ");
//            MessageWidget& msg2 = r->room_inside->append_other_message("Hi!");
//            r->room_inside->show_message(&msg1);
//            r->room_inside->show_message(&msg2);
//        }
//    }

//    NewRoomWidget& new_room = make_creation_new_room();
//    show_creation_new_room(&new_room);
//    for (int i = 0; i < 1; ++i) {
//        QWidget &chb1 = new_room.make_checkbox_for_person("Ilia");
//        new_room.show_checkbox_for_person(&chb1);
//    }
//    for (int i = 0; i < 1; ++i) {
//        QWidget &chb1 = new_room.make_checkbox_for_person("Vasiliy");
//        new_room.show_checkbox_for_person(&chb1);
//    }
//    for (int i = 0; i < 1; ++i) {
//        QWidget &chb1 = new_room.make_checkbox_for_person("Igor");
//        new_room.show_checkbox_for_person(&chb1);
//    }
//    new_room.deleteLater();
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

    rooms_widget = new QWidget(this);
    scroll_rooms_widget = new QScrollArea(this);
    top_widget = new QWidget(this);
    search_line_edit = new QLineEdit(top_widget);
    search_line_edit->setPlaceholderText("Поиск...");
    creating_new_room_button = new QPushButton(top_widget);

    scroll_rooms_widget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll_rooms_widget->setWidget(rooms_widget);
    scroll_rooms_widget->setStyleSheet(current_style.rooms_space_scroll_bar);
    scroll_rooms_widget->setMinimumSize(width_rooms_area + delta, this->height() - 50);
    scroll_rooms_widget->move(0, 49);
    scroll_rooms_widget->show();

    rooms_widget->setFixedSize(width_rooms_area, this->height() - 50);
    rooms_widget->setStyleSheet(current_style.rooms_space_widget);

    top_widget->setFixedSize(rooms_widget->width() + 1, 50);
    top_widget->setStyleSheet(current_style.top_widget);
    top_widget->show();

    search_line_edit->setFixedSize(196, 30);
    search_line_edit->setStyleSheet(current_style.line_edit_standard);
    search_line_edit->move(10, 10);
    search_line_edit->show();

    creating_new_room_button->setFixedSize(30, 30);
    creating_new_room_button->setText("+");
    creating_new_room_button->setStyleSheet(current_style.button_create_new_room);
    creating_new_room_button->move(213, 10);
}

void MainWindow::show_room_icon(const Room &room) {
    room.room_icon->room_icon_->setParent(rooms_widget);

    int room_icon_height = room.room_icon->room_icon_->height();
    int height = index * room_icon_height + delta;
    ++index;

    if (height >= this->height()) {
        rooms_widget->setFixedHeight(height + room_icon_height - 1);
    }

    room.room_icon->room_icon_->move(delta, height);
    room.room_icon->room_icon_->show();
}

void MainWindow::show_room_inside(Room &room) {
    room.room_inside->room_inside_->setParent(this);
    room.room_inside->room_inside_->move(width_rooms_area + delta, 0);
    room.room_inside->room_inside_->setFixedSize(this->width() - width_rooms_area - delta, this->height());
    room.room_inside->room_inside_->show();

    room.set_room_name_at_top(room.get_room_name());
    room.room_inside->inside_room_name_label->setStyleSheet(current_style.inside_room_name_label);
    QSize inside_room_name_label_size_base = room.room_inside->inside_room_name_label->sizeHint();
    int inside_room_name_label_width = 0;
    if (inside_room_name_label_size_base.width() % 2 == 0) {
        inside_room_name_label_width = inside_room_name_label_size_base.width();
    }
    else {
        inside_room_name_label_width = inside_room_name_label_size_base.width() + 1;
    }

    room.room_inside->message_line_area_widget->setFixedSize(room.room_inside->room_inside_->width(), 48);
    room.room_inside->message_line_area_widget->move(0, this->height() - room.room_inside->message_line_area_widget->height());
    room.room_inside->message_line_area_widget->setStyleSheet(current_style.message_line_area_widget);
    room.room_inside->message_line_area_widget->show();

    room.room_inside->inside_room_name_label->setFixedSize(inside_room_name_label_width, 30);
    room.room_inside->inside_room_name_label->setAlignment(Qt::AlignCenter);
    room.room_inside->inside_room_name_label->move((room.room_inside->room_inside_->width() - room.room_inside->inside_room_name_label->width()) / 2, 10);
    room.room_inside->inside_room_name_label->show();

    room.room_inside->inside_room_name_widget->move(0, 0);
    room.room_inside->inside_room_name_widget->setFixedSize(room.room_inside->room_inside_->width(), 50);
    room.room_inside->inside_room_name_widget->setStyleSheet(current_style.inside_room_name_widget);
    room.room_inside->inside_room_name_widget->show();

    room.room_inside->message_line->setFixedSize(700, 47);
    room.room_inside->message_line->move(0, 1);
    room.room_inside->message_line->setStyleSheet(current_style.inside_message_line);
    room.room_inside->message_line->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    room.room_inside->inside_messages_widget->setStyleSheet(current_style.inside_messages_widget);
    room.room_inside->inside_messages_widget->setFixedSize(room.room_inside->room_inside_->width() - 2,
                                                           room.room_inside->room_inside_->height() -
                                                           room.room_inside->message_line_area_widget->height() -
                                                           room.room_inside->inside_room_name_widget->height() - 2);

    room.room_inside->inside_messages_scroll_area->move(0, room.room_inside->inside_room_name_widget->height());
    room.room_inside->inside_messages_scroll_area->setFixedSize(room.room_inside->inside_messages_widget->width() + 2,
                                                                room.room_inside->inside_messages_widget->height() + 2);
    room.room_inside->inside_messages_scroll_area->setWidget(room.room_inside->inside_messages_widget);
    room.room_inside->inside_messages_scroll_area->setStyleSheet(current_style.inside_messages_widget);

    room.room_inside->send_message_button->setGeometry(room.room_inside->message_line->width() + 5, 8, 32, 32);
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

    new_room_widget->create_new_room_top_widget->move(0, 0);
    new_room_widget->create_new_room_top_widget->setFixedSize(new_room_widget->create_new_room_widget->width(), 51);
    new_room_widget->create_new_room_top_widget->setStyleSheet(current_style.create_new_room_top_widget);
    new_room_widget->create_new_room_top_widget->show();

    new_room_widget->create_new_room_bottom_widget->move(0, 602);
    new_room_widget->create_new_room_bottom_widget->setFixedSize(new_room_widget->create_new_room_widget->width(), 98);
    new_room_widget->create_new_room_bottom_widget->setStyleSheet(current_style.create_new_room_bottom_widget);
    new_room_widget->create_new_room_bottom_widget->show();

    new_room_widget->new_room_name_line_edit->move(99, 10);
    new_room_widget->new_room_name_line_edit->setFixedSize(550, 30);
    new_room_widget->new_room_name_line_edit->setStyleSheet(current_style.line_edit_standard);
    new_room_widget->new_room_name_line_edit->show();

    new_room_widget->users_search_line_edit->move(48, 10);
    new_room_widget->users_search_line_edit->setFixedSize(700 - 12, 30);
    new_room_widget->users_search_line_edit->setStyleSheet(current_style.line_edit_standard);
    new_room_widget->users_search_line_edit->show();

    new_room_widget->select_users_widget->setFixedSize(new_room_widget->create_new_room_widget->width() - 2,
                                                       new_room_widget->create_new_room_widget->height() -
                                                       new_room_widget->create_new_room_top_widget->height() -
                                                       new_room_widget->create_new_room_bottom_widget->height() - 2);
    new_room_widget->select_users_widget->setStyleSheet(current_style.select_people_widget);

    new_room_widget->select_users_scroll_area->setWidget(new_room_widget->select_users_widget);
    new_room_widget->select_users_scroll_area->move(0, new_room_widget->new_room_name_line_edit->height() + 20);
    new_room_widget->select_users_scroll_area->setFixedSize(new_room_widget->select_users_widget->width() + 2, new_room_widget->select_users_widget->height() + 2);
    new_room_widget->select_users_scroll_area->setStyleSheet("");

    new_room_widget->cancel_create_new_room_button->move(12, 13);
    new_room_widget->cancel_create_new_room_button->setStyleSheet(current_style.back_to_authorization_button);
    new_room_widget->cancel_create_new_room_button->show();

    new_room_widget->create_new_room_button->setStyleSheet(current_style.button_standard);
    new_room_widget->create_new_room_button->move(314, 50);
    new_room_widget->create_new_room_button->show();
}

QString MainWindow::get_search_line_edit() {
    return search_line_edit->text();
}

MainWindow::~MainWindow()
{
    delete ui;
}


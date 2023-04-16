#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <Graphics/RoomIconWidget.h>
#include <QScrollArea>
#include <Graphics/Room.h>
#include <Graphics/MessageWidget.h>
#include <Graphics/RoomInsideWidget.h>
#include <QCheckBox>
#include <QSize>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {}

void MainWindow::show_main_window() {
    new_room = &make_creation_new_room();
    make_window_skillet();
    this->setWindowTitle("HOKS");

    connect(this, &MainWindow::show_checkbox_signal, new_room, &NewRoomWidget::show_checkox);
    connect(new_room, &NewRoomWidget::creating_new_room_signal, this, &MainWindow::push_on_finish_create_room_signal);
    connect(this, &MainWindow::hide_create_room, new_room, &NewRoomWidget::hide_create_room);
    connect(creating_new_room_button, &QPushButton::clicked, this, &MainWindow::push_on_creating_new_room_slot);

    show();
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

    left_widget = new QWidget(this);
    left_widget->setFixedSize(width_rooms_area + 2, height());
    left_widget->setStyleSheet(current_style.left_widget);

    rooms_widget = new QWidget(left_widget);
    scroll_rooms_widget = new QScrollArea(left_widget);

    top_widget = new QWidget(left_widget);
    search_line_edit = new QLineEdit(top_widget);
    search_line_edit->setPlaceholderText("Поиск...");
    creating_new_room_button = new QPushButton(top_widget);

    scroll_rooms_widget->setWidget(rooms_widget);
    scroll_rooms_widget->setStyleSheet(current_style.scroll_rooms_widget);
    scroll_rooms_widget->setMinimumSize(width_rooms_area - 1 + delta, this->height() - 50);
    scroll_rooms_widget->move(0, 49);

    rooms_widget->setFixedSize(width_rooms_area - 9, this->height() - 52);
    rooms_widget->setStyleSheet(current_style.rooms_space_widget);

    top_widget->setFixedSize(width_rooms_area, 50);
    top_widget->setStyleSheet(current_style.top_widget);
    top_widget->show();

    search_line_edit->setFixedSize(196, 30);
    search_line_edit->setStyleSheet(current_style.line_edit_standard);
    set_standard_line_edit_placeholder_color(search_line_edit);
    search_line_edit->move(10, 10);
    search_line_edit->show();

    creating_new_room_button->setFixedSize(30, 30);
    creating_new_room_button->setText("+");
    creating_new_room_button->setStyleSheet(current_style.button_create_new_room);
    creating_new_room_button->move(213, 10);
}

void MainWindow::set_standard_line_edit_placeholder_color(QLineEdit *line_edit) {
    QPalette palette = line_edit->palette();
    QColor color = QColor(102, 102, 102);
    palette.setColor(QPalette::PlaceholderText, color);
    line_edit->setPalette(palette);
}

void MainWindow::set_standard_line_edit_placeholder_color(QTextEdit *line_edit) {
    QPalette palette = line_edit->palette();
    QColor color = QColor(102, 102, 102);
    palette.setColor(QPalette::PlaceholderText, color);
    line_edit->setPalette(palette);
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

void MainWindow::hide_room_inside(Room &room) {
    room.room_inside->room_inside_->hide();
}

void MainWindow::hide_room_icon(Room &room) {
    room.room_icon->room_icon_->hide();
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
    room.room_inside->message_line->move(1, 1);
    room.room_inside->message_line->setStyleSheet(current_style.inside_message_line);
    set_standard_line_edit_placeholder_color(room.room_inside->message_line);
    room.room_inside->message_line->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    if (room.first_use) {
        room.first_use = false;
        room.room_inside->inside_messages_widget->setStyleSheet(current_style.inside_messages_widget);

        room.room_inside->inside_messages_widget->setFixedSize(room.room_inside->room_inside_->width() - 8,
                                                               room.room_inside->room_inside_->height() -
                                                               room.room_inside->message_line_area_widget->height() -
                                                               room.room_inside->inside_room_name_widget->height() - 2);

        room.room_inside->inside_messages_scroll_area->move(0, room.room_inside->inside_room_name_widget->height());
        room.room_inside->inside_messages_scroll_area->setFixedSize(room.room_inside->inside_messages_widget->width() + 8,
                                                                    room.room_inside->inside_messages_widget->height() + 2);
        room.room_inside->inside_messages_scroll_area->setStyleSheet(current_style.scroll_bar_standard);
    }

    room.room_inside->send_message_button->setGeometry(room.room_inside->message_line->width() + 5, 8, 32, 32);
    room.room_inside->send_message_button->setStyleSheet(current_style.send_message_button);
}

void MainWindow::draw_creation_new_room(NewRoomWidget* new_room_widget) {
    new_room_widget->create_new_room_widget->setParent(this);
    new_room_widget->create_new_room_widget->show();
    new_room_widget->select_users_scroll_area->setParent(new_room_widget->create_new_room_widget);

    new_room_widget->create_new_room_widget->setFixedSize(this->width() - width_rooms_area - delta, this->height());
    new_room_widget->create_new_room_widget->setStyleSheet(current_style.create_new_room_widget);
    new_room_widget->create_new_room_widget->move(width_rooms_area + delta, 0);


    new_room_widget->create_new_room_top_widget->move(0, 0);
    new_room_widget->create_new_room_top_widget->setFixedSize(new_room_widget->create_new_room_widget->width(), 50);
    new_room_widget->create_new_room_top_widget->setStyleSheet(current_style.create_new_room_top_widget);
    new_room_widget->create_new_room_top_widget->show();

    new_room_widget->create_new_room_bottom_widget->move(0, 602);
    new_room_widget->create_new_room_bottom_widget->setFixedSize(new_room_widget->create_new_room_widget->width(), 98);
    new_room_widget->create_new_room_bottom_widget->setStyleSheet(current_style.create_new_room_bottom_widget);
    new_room_widget->create_new_room_bottom_widget->show();

    new_room_widget->new_room_name_line_edit->move(99, 10);
    new_room_widget->new_room_name_line_edit->setFixedSize(550, 30);
    new_room_widget->new_room_name_line_edit->setStyleSheet(current_style.new_room_name_line_edit);
    set_standard_line_edit_placeholder_color(new_room_widget->new_room_name_line_edit);
    new_room_widget->new_room_name_line_edit->show();

    new_room_widget->users_search_line_edit->move(48, 10);
    new_room_widget->users_search_line_edit->setFixedSize(700 - 12, 30);
    new_room_widget->users_search_line_edit->setStyleSheet(current_style.new_room_name_line_edit);
    set_standard_line_edit_placeholder_color(new_room_widget->users_search_line_edit);
    new_room_widget->users_search_line_edit->show();

    new_room_widget->select_users_widget->setFixedSize(new_room_widget->create_new_room_widget->width() - 10,
                                                       new_room_widget->create_new_room_widget->height() -
                                                       new_room_widget->create_new_room_top_widget->height() -
                                                       new_room_widget->create_new_room_bottom_widget->height() - 2);
    new_room_widget->select_users_widget->setStyleSheet(current_style   .select_people_widget);

    new_room_widget->create_new_room_widget->setParent(this);
    new_room_widget->select_users_widget->show();

    new_room_widget->select_users_scroll_area->setWidget(new_room_widget->select_users_widget);
    new_room_widget->select_users_scroll_area->move(0, new_room_widget->new_room_name_line_edit->height() + 20);
    new_room_widget->select_users_scroll_area->setFixedSize(new_room_widget->select_users_widget->width() + 10, new_room_widget->select_users_widget->height() + 2);
    new_room_widget->select_users_scroll_area->setStyleSheet(current_style.scroll_bar_standard);

    new_room_widget->cancel_create_new_room_button->move(12, 13);
    new_room_widget->cancel_create_new_room_button->setStyleSheet(current_style.back_to_authorization_button);
    new_room_widget->cancel_create_new_room_button->show();

    new_room_widget->create_new_room_button->setStyleSheet(current_style.button_standard);
    new_room_widget->create_new_room_button->move(314, 50);
    new_room_widget->create_new_room_button->show();
    new_room_widget->select_users_widget->show();
    new_room_widget->select_users_scroll_area->show();

    new_room_widget->users_search_line_edit->setText("");
    new_room_widget->new_room_name_line_edit->setText("");

    new_room_widget->index = 0;
    QList<QObject*> checkboxes = new_room_widget->select_users_widget->children();
    for(int i = 0; i < checkboxes.size(); ++i) {
        QObject* checkbox = checkboxes.at(i);
        if(QWidget* widget = qobject_cast<QWidget*>(checkbox)) {
            widget->hide();
        }
    }
}

QString MainWindow::get_search_line_edit() {
    return search_line_edit->text();
}

void MainWindow::slot_open_main_window() {
    show_main_window();
}

void MainWindow::push_on_creating_new_room_slot() {
    emit push_on_creating_new_room_signal();
}

void MainWindow::show_checkbox(const QString &chechbox_name) {
    emit show_checkbox_signal(chechbox_name);
}

void MainWindow::show_creation_new_room() {
    draw_creation_new_room(new_room);
}

void MainWindow::slot_hide_create_room() {
    emit hide_create_room();
}

NewRoomWidget& MainWindow::make_creation_new_room() {
    NewRoomWidget *new_room_widget = new NewRoomWidget();
    new_room_widget->setParent(this);
    return *new_room_widget;
}

void MainWindow::push_on_finish_create_room_slot(const QList<QString>& peoples, const QString& room_name) {
    emit push_on_finish_create_room_signal(peoples, room_name);
}

MainWindow::~MainWindow()
{
    delete ui;
}

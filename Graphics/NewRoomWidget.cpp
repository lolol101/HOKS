#include "NewRoomWidget.h"
#include "ui_NewRoomWidget.h"
#include <QDebug>

NewRoomWidget::NewRoomWidget()
{
    ui->setupUi(this);
    create_new_room_widget = new QWidget();
    create_new_room_top_widget = new QWidget(create_new_room_widget);
    create_new_room_bottom_widget = new QWidget(create_new_room_widget);
    new_room_name_line_edit = new QLineEdit(create_new_room_bottom_widget);
    new_room_name_line_edit->setPlaceholderText("Название комнаты...");
    users_search_line_edit = new QLineEdit(create_new_room_top_widget);
    users_search_line_edit->setPlaceholderText("Найдите нужных Вам пользователей");

    select_users_widget = new QWidget(create_new_room_widget);

    select_users_scroll_area = new QScrollArea(select_users_widget);

    create_new_room_button = new QPushButton(create_new_room_bottom_widget);
    create_new_room_button->setText("Создать");
    create_new_room_button->setFixedSize(120, 38);
    cancel_create_new_room_button = new QPushButton(create_new_room_top_widget);
    cancel_create_new_room_button->setFixedSize(24, 24);
    connect(create_new_room_button, &QPushButton::clicked, this, &NewRoomWidget::push_on_creating_new_room_button);
    connect(cancel_create_new_room_button, &QPushButton::clicked, this, &NewRoomWidget::push_on_cancel_button_slot);
}

QWidget &NewRoomWidget::make_checkbox_for_person(const QString &person_name) {
    QWidget *widget_for_checkbox = new QWidget(select_users_widget);
    widget_for_checkbox->setFixedSize(select_users_widget->width(), 40);
    widget_for_checkbox->move(0, index * 40);
    widget_for_checkbox->setStyleSheet(current_style.person_checkbox_widget);

    QCheckBox *checkbox_for_person = new QCheckBox(person_name, widget_for_checkbox);

    checkbox_for_person->setStyleSheet(current_style.person_checkbox);
    checkbox_for_person->move(15, 9);

    connect(checkbox_for_person, &QCheckBox::stateChanged, this, &NewRoomWidget::person_checkbox_changed_slot);

    if ((index + 1) * 40 >= select_users_widget->height()) {
        select_users_widget->setFixedHeight((index + 1) * 40 - 2);
    }
    ++index;

    return *widget_for_checkbox;
}

void NewRoomWidget::show_checkox(const QString &checkbox_name) {
    show_checkbox_for_person(&make_checkbox_for_person(checkbox_name));
}


void NewRoomWidget::person_checkbox_changed_slot(int state) {
    QCheckBox *now_sender = static_cast<QCheckBox*>(sender());
    QString new_user_name = now_sender->text();
    if (state == Qt::Checked) {
        clicked_users.append(new_user_name);
    }
    else {
        clicked_users.removeAt(clicked_users.indexOf(new_user_name));
    }
}

void NewRoomWidget::push_on_creating_new_room_button() {
    emit creating_new_room_signal(clicked_users, new_room_name_line_edit->text());
}

void NewRoomWidget::show_checkbox_for_person(QWidget *person_checkbox) {
    person_checkbox->show();
}


QString NewRoomWidget::get_new_room_name_line_edit() {
    return new_room_name_line_edit->text();
}

QString NewRoomWidget::get_users_search_line_edit() {
    return users_search_line_edit->text();
}

void NewRoomWidget::push_on_cancel_button_slot() {
    create_new_room_widget->hide();
}

NewRoomWidget::~NewRoomWidget()
{
    delete ui;
}

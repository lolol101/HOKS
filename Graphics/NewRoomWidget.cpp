#include "NewRoomWidget.h"
#include "ui_NewRoomWidget.h"

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
}

QWidget &NewRoomWidget::make_checkbox_for_person(const QString &person_name) {
    QWidget *widget_for_checkbox = new QWidget(select_users_widget);
    widget_for_checkbox->setFixedSize(select_users_widget->width(), 40);
    widget_for_checkbox->move(0, index * 40);
    widget_for_checkbox->setStyleSheet(current_style.person_checkbox_widget);

    QCheckBox *checkbox_for_person = new QCheckBox(person_name, widget_for_checkbox);
    checkbox_for_person->setStyleSheet(current_style.person_checkbox);
    checkbox_for_person->move(15, 9);

    if ((index + 1) * 40 >= select_users_widget->height()) {
        select_users_widget->setFixedHeight((index + 1) * 40 - 2);
    }
    ++index;

    widget_for_checkbox->hide();
    return *widget_for_checkbox;
}

bool NewRoomWidget::is_checkbox_checked(QCheckBox *person_checkbox) {
    return person_checkbox->checkState() == Qt::Checked;
}

void NewRoomWidget::show_checkbox_for_person(QWidget *person_checkbox) {
    person_checkbox->show();
}

void NewRoomWidget::person_checkbox_changed() {
    qDebug() << "Checked!";
}

QString NewRoomWidget::get_new_room_name_line_edit() {
    return new_room_name_line_edit->text();
}

QString NewRoomWidget::get_users_search_line_edit() {
    return users_search_line_edit->text();
}

NewRoomWidget::~NewRoomWidget()
{
    delete ui;
}

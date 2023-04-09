#include "NewRoomWidget.h"
#include "ui_NewRoomWidget.h"

NewRoomWidget::NewRoomWidget()
{
    ui->setupUi(this);
    create_new_room_widget = new QWidget();
    new_room_name_line_edit = new QLineEdit(create_new_room_widget);
    users_search_line_edit = new QLineEdit(create_new_room_widget);
    room_name_label = new QLabel(create_new_room_widget);
    room_name_label->setText("Название комнаты");
    select_users_widget = new QWidget(create_new_room_widget);
    select_users_scroll_area = new QScrollArea(select_users_widget);
    create_new_room_button = new QPushButton(create_new_room_widget);
    create_new_room_button->setText("Создать");
    create_new_room_button->setFixedSize(120, 38);
    cancel_create_new_room_button = new QPushButton(create_new_room_widget);
    cancel_create_new_room_button->setText("Отмена");
    cancel_create_new_room_button->setFixedSize(120, 38);
}

QWidget &NewRoomWidget::make_checkbox_for_person(const QString &person_name) {
    QWidget *widget_for_checkbox = new QWidget(select_users_widget);
    widget_for_checkbox->setFixedSize(200, 35);
    QCheckBox *checkbox_for_person = new QCheckBox(person_name, widget_for_checkbox);
    widget_for_checkbox->move(15, 10 + index * 35);
    checkbox_for_person->setStyleSheet(current_style.person_checkbox);
    widget_for_checkbox->setStyleSheet(current_style.person_checkbox_widget);
    if (index * 20 >= select_users_widget->height()) {
        select_users_widget->setFixedHeight(index * 20 + 40);
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

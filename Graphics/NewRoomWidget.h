#ifndef NEWROOMWIDGET_H
#define NEWROOMWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>

namespace Ui {
class NewRoomWidget;
}

class NewRoomWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NewRoomWidget(QWidget *parent = nullptr);

    QWidget *create_new_room_widget;

    QLineEdit *new_room_name_line_edit;

    QWidget *select_people_widget;

    QCheckBox &make_checkbox_for_person(const QString &person_name);

    void show_checkbox_for_person(QCheckBox& person);

    QPushButton *create_new_room_button;

    QPushButton *cancel_create_new_room_button;

    ~NewRoomWidget();

private:
    Ui::NewRoomWidget *ui;
};

#endif // NEWROOMWIDGET_H

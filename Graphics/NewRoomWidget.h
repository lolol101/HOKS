#ifndef NEWROOMWIDGET_H
#define NEWROOMWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QScrollArea>
#include <appstyle.h>

namespace Ui {
class NewRoomWidget;
}

class NewRoomWidget : public QWidget
{
    Q_OBJECT

public:
    NewRoomWidget();

    style_table current_style;

    QWidget *create_new_room_widget;

    QLineEdit *new_room_name_line_edit;

    QWidget *select_people_widget;

    QScrollArea *select_people_scroll_area;

    QWidget &make_checkbox_for_person(const QString &person_name);

    void show_checkbox_for_person(QWidget *person_checkbox);

    bool is_checkbox_checked(QCheckBox *person_checkbox);

    QPushButton *create_new_room_button;

    QPushButton *cancel_create_new_room_button;

    int index = 0;

    ~NewRoomWidget();

private:
    Ui::NewRoomWidget *ui;

public slots:
    void person_checkbox_changed();
};

#endif // NEWROOMWIDGET_H

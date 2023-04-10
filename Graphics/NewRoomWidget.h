#ifndef NEWROOMWIDGET_H
#define NEWROOMWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QScrollArea>
#include <appstyle.h>
#include <QLabel>

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

    QLineEdit *users_search_line_edit;

    QString get_new_room_name_line_edit();

    QString get_users_search_line_edit();

    QWidget *select_users_widget;

    QWidget *create_new_room_top_widget;

    QWidget *create_new_room_bottom_widget;

    QScrollArea *select_users_scroll_area;

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

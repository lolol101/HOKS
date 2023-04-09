#include "RoomInsideWidget.h"
#include "QtWidgets/qlabel.h"
#include "ui_RoomInsideWidget.h"
#include "MessageWidget.h"
#include <QLabel>

RoomInsideWidget::RoomInsideWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoomInsideWidget)
{
    ui->setupUi(this);
}

RoomInsideWidget::RoomInsideWidget() {
    room_inside_ = new QWidget();
    message_line = new QTextEdit(room_inside_);
    inside_room_name = new QWidget(room_inside_);

    inside_messages_widget = new QWidget(room_inside_);
    inside_messages_scroll_area = new QScrollArea(room_inside_);
    inside_messages_scroll_area->setWidget(inside_messages_widget);
    inside_messages_scroll_area->setFixedSize(room_inside_->width(), room_inside_->height() - 100);
}

MessageWidget& RoomInsideWidget::append_user_message(const QString &message_text) {
    MessageWidget *message_widget = new MessageWidget(inside_messages_widget);
    QLabel *message_text_label = new QLabel(message_widget);
    message_widget->setFixedSize(400, 100);
    int message_widget_height = message_widget->height();
    int message_coordinate = index * message_widget_height + 2 + index * 4;
    ++index;

    if (message_coordinate >= inside_messages_widget->height()) {
        inside_messages_widget->setFixedSize(inside_messages_widget->width(), message_coordinate);
    }

    message_widget->setStyleSheet(current_style.messages_widget);
    message_widget->move(320, message_coordinate);

    message_text_label->setText(message_text);
    message_text_label->setFixedSize(message_widget->width(), message_widget->height());
    message_text_label->setStyleSheet(current_style.messages_label);

    message_widget->hide();
    return *message_widget;
}

MessageWidget& RoomInsideWidget::append_other_message(const QString &message_text) {
    MessageWidget *message_widget = new MessageWidget(inside_messages_widget);
    QLabel *message_text_label = new QLabel(message_widget);
    message_widget->setFixedSize(400, 100);
    int message_widget_height = message_widget->height();
    int message_coordinate = index * message_widget_height + 2 + index * 4;;
    ++index;

    if (message_coordinate >= inside_messages_widget->height()) {
        inside_messages_widget->setFixedSize(inside_messages_widget->width(), message_coordinate);
    }

    message_widget->setStyleSheet(current_style.messages_widget);
    message_widget->move(5, message_coordinate);

    message_text_label->setText(message_text);
    message_text_label->setFixedSize(message_widget->width(), message_widget->height());
    message_text_label->setStyleSheet(current_style.messages_label);

    message_widget->hide();
    return *message_widget;
}

void RoomInsideWidget::show_message(MessageWidget *message_widget) {
    message_widget->show();
}

RoomInsideWidget::~RoomInsideWidget()
{
    delete ui;
}

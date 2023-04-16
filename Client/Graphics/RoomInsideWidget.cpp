#include "RoomInsideWidget.h"
#include "QtWidgets/qlabel.h"
#include "ui_RoomInsideWidget.h"
#include "MessageWidget.h"
#include <QLabel>
#include <QTextEdit>
#include <QFontMetrics>


RoomInsideWidget::RoomInsideWidget() {
    room_inside_ = new QWidget();
    message_line_area_widget = new QWidget(room_inside_);
    message_line = new QTextEdit(message_line_area_widget);
    message_line->setPlaceholderText("Сообщение...");
    inside_room_name_widget = new QWidget(room_inside_);
    inside_room_name_label = new QLabel(inside_room_name_widget);

    inside_messages_widget = new QWidget(room_inside_);
    inside_messages_scroll_area = new QScrollArea(room_inside_);
    inside_messages_scroll_area->setWidget(inside_messages_widget);

    send_message_button = new QPushButton(message_line_area_widget);

    connect(send_message_button, &QPushButton::clicked, this, &RoomInsideWidget::slot_clicked_send_button);
}

MessageWidget& RoomInsideWidget::append_user_message(const QString &message_text) {
    MessageWidget *message_widget = new MessageWidget(inside_messages_widget);
    QLabel *message_text_label = new QLabel(message_widget);
    message_widget->setFixedSize(400, 100);
    int message_widget_height = message_widget->height();
    int message_coordinate = index * message_widget_height + 2 + index * 4;;
    ++index;

    if (message_coordinate >= inside_messages_widget->height() - message_widget->height() - 8) {
        inside_messages_widget->setFixedSize(inside_messages_scroll_area->width() - 10, message_coordinate + message_widget_height + 8);
    }

    message_widget->setStyleSheet(current_style.messages_widget);
    message_widget->move(332, message_coordinate);

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
    int message_coordinate = index * message_widget_height + 2 + index * 4;
    ++index;

    if (message_coordinate >= inside_messages_widget->height() - message_widget->height() - 8) {
        inside_messages_widget->setFixedSize(inside_messages_scroll_area->width() - 10, message_coordinate + message_widget_height + 8);
    }

    message_widget->setStyleSheet(current_style.messages_widget);
    message_widget->move(10, message_coordinate);

    message_text_label->setText(message_text);
    message_text_label->setFixedSize(message_widget->width(), message_widget->height());
    message_text_label->setStyleSheet(current_style.messages_label);

    message_widget->hide();
    return *message_widget;
}

void RoomInsideWidget::show_message(MessageWidget *message_widget) {
    message_widget->show();
}

QString RoomInsideWidget::get_message_line() {
    return message_line->toPlainText();
}

void RoomInsideWidget::set_room_name(const QString &room_name) {
    this->inside_room_name_label->setText(room_name);
}

RoomInsideWidget::~RoomInsideWidget() {
    delete ui;
}

void RoomInsideWidget::slot_clicked_send_button() {
    QString msg = message_line->toPlainText();
    emit clicked_send_button(msg);
    message_line->clear();
}

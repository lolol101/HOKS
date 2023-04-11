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
    inside_messages_scroll_area->setFixedSize(room_inside_->width(), room_inside_->height() - 100);

    send_message_button = new QPushButton(message_line_area_widget);
}

MessageWidget& RoomInsideWidget::append_user_message(const QString &message_text) {
    MessageWidget *message_widget = new MessageWidget(inside_messages_widget);
    QLabel *message_text_label = new QLabel(message_widget);
    int message_widget_height = message_widget->height();
    int message_coordinate = index * message_widget_height + 2 + index * 4;
    ++index;

    if (message_coordinate >= inside_messages_widget->height()) {
        inside_messages_widget->setFixedSize(inside_messages_widget->width(), message_coordinate);
    }

    message_widget->setStyleSheet(current_style.messages_widget);
    message_widget->move(320, message_coordinate);

    message_text_label->setText(message_text);
    message_text_label->setStyleSheet(current_style.messages_label);
    QSize message_text_label_size = message_text_label->sizeHint();

    message_text_label->setFixedSize(message_text_label_size.width(), message_text_label_size.height());
    message_text_label->move(10, 10);
    message_text_label->setAlignment(Qt::AlignLeft);

    message_widget->setFixedSize(message_text_label->width() + 20, message_text_label->height() + 20);
    qDebug() << message_widget->width() << message_widget->height();


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

QString RoomInsideWidget::get_message_line() {
    return message_line->toPlainText();
}

void RoomInsideWidget::set_room_name(const QString &room_name) {
    this->inside_room_name_label->setText(room_name);
}

RoomInsideWidget::~RoomInsideWidget() {
    delete ui;
}

void RoomInsideWidget::slot_clicked_send_button(const QString& text_message) {
    emit clicked_send_button(text_message);
}

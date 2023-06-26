#include "RoomInsideWidget.h"
#include "QtWidgets/qlabel.h"
#include "ui_RoomInsideWidget.h"
#include "MessageWidget.h"
#include <QLabel>
#include <QTextEdit>
#include <QFontMetrics>
#include <QScrollBar>
#include <Graphics/MessageLine.h>
#include <iostream>

RoomInsideWidget::RoomInsideWidget() {
    room_inside_ = new QWidget();
    message_line_area_widget = new QWidget(room_inside_);
    message_line = new MessageLine(message_line_area_widget);
    message_line->setPlaceholderText("Сообщение...");
    inside_room_name_widget = new QWidget(room_inside_);
    inside_room_name_label = new QLabel(inside_room_name_widget);

    inside_messages_widget = new QWidget(room_inside_);
    inside_messages_scroll_area = new QScrollArea(room_inside_);
    inside_messages_scroll_area->setWidget(inside_messages_widget);

    send_message_button = new QPushButton(message_line_area_widget);
    clip_button = new QPushButton(message_line_area_widget);

    connect(clip_button, &QPushButton::clicked, this, &RoomInsideWidget::slot_clicked_clip_button);
    connect(send_message_button, &QPushButton::clicked, this, &RoomInsideWidget::slot_clicked_send_button);
    connect(message_line, &MessageLine::push_on_enter_to_send_signal, this, &RoomInsideWidget::slot_clicked_send_button);
}

MessageWidget& RoomInsideWidget::append_user_message(const QString &message_text, const QString &author, bool is_media) {
    MessageWidget *message_widget = new MessageWidget(inside_messages_widget);
    message_widget->setFixedSize(400, 100);

    QLabel *size_retainer = new QLabel(message_widget);

    size_retainer->setGeometry(0, 0, message_widget->width(), message_widget->height());

    QLabel *message_text_label = new QLabel(message_widget);

    int message_widget_height = message_widget->height();
    int message_coordinate = index * message_widget_height + 2 + index * 4;;
    ++index;

    if (message_coordinate >= inside_messages_widget->height() - message_widget->height() - 8) {
        inside_messages_widget->setFixedSize(inside_messages_scroll_area->width() - 10, message_coordinate + message_widget_height + 8);
    }

    message_widget->setStyleSheet(current_style.messages_widget);
    message_widget->move(332, message_coordinate);

    message_text_label->setText(message_text);

    if (is_media) {
        message_widget->setFixedSize(400, 100);
        message_widget->sent_file_icon = new QPushButton(message_widget);

        message_widget->sent_file_icon->setGeometry(15, 28, 45, 45);
        message_widget->sent_file_icon->setStyleSheet(current_style.sent_file_icon);
        message_text_label->setGeometry(60, 42, 336, 30);
        message_text_label->setStyleSheet(current_style.file_name);

        message_widget->open_file_button = new QPushButton(message_widget);
        message_widget->open_file_button->setGeometry(60, 60, 60, 30);
        message_widget->open_file_button->setText("Открыть");
        message_widget->open_file_button->setStyleSheet(current_style.open_file_button);

        message_widget->connect_signals_to_slots();

        message_widget->file_name = message_text;
        message_widget->author = author;
        message_widget->is_media = is_media;
        connect(message_widget, &MessageWidget::signal_clicked_open_button, this,
        &RoomInsideWidget::slot_open_file_button);
    } else {
        message_text_label->setStyleSheet(current_style.messages_label);
        message_text_label->setFixedSize(message_widget->width(), message_widget->height());
    }

    message_widget->hide();
    return *message_widget;
}
MessageWidget& RoomInsideWidget::append_other_message(const QString &message_text, const QString &author, bool is_media) {
    MessageWidget *message_widget = new MessageWidget(inside_messages_widget);
    message_widget->setFixedSize(400, 100);

    QLabel *size_retainer = new QLabel(message_widget);

    size_retainer->setGeometry(0, 0, message_widget->width(), message_widget->height());

    QLabel *message_text_label = new QLabel(message_widget);
    QLabel *author_label = new QLabel(message_widget);
    author_label->setText(author);
    author_label->setGeometry(11, 9, 390, 15);

    int message_widget_height = message_widget->height();
    int message_coordinate = index * message_widget_height + 2 + index * 4;;
    ++index;

    if (message_coordinate >= inside_messages_widget->height() - message_widget->height() - 8) {
        inside_messages_widget->setFixedSize(inside_messages_scroll_area->width() - 10, message_coordinate + message_widget_height + 8);
    }

    message_widget->setStyleSheet(current_style.messages_widget);
    message_widget->move(10, message_coordinate);

    message_text_label->setText(message_text);

    if (is_media) {
        message_widget->setFixedSize(400, 100);
        message_widget->sent_file_icon = new QPushButton(message_widget);

        message_widget->sent_file_icon->setGeometry(15, 28, 45, 45);
        message_widget->sent_file_icon->setStyleSheet(current_style.sent_file_icon);
        message_text_label->setGeometry(60, 42, 336, 30);
        message_text_label->setStyleSheet(current_style.file_name);

        message_widget->open_file_button = new QPushButton(message_widget);
        message_widget->open_file_button->setGeometry(60, 60, 60, 30);
        message_widget->open_file_button->setText("Открыть");
        message_widget->open_file_button->setStyleSheet(current_style.open_file_button);

        message_widget->connect_signals_to_slots();

        message_widget->file_name = message_text;
        message_widget->author = author;
        message_widget->is_media = is_media;
        connect(message_widget, &MessageWidget::signal_clicked_open_button, this,
        &RoomInsideWidget::slot_open_file_button);
    } else {
        message_text_label->setStyleSheet(current_style.messages_label);
        message_text_label->setFixedSize(message_widget->width(), message_widget->height());
    }

    message_widget->hide();
    return *message_widget;
}

void RoomInsideWidget::show_message(MessageWidget *message_widget) {
    message_widget->show();
    inside_messages_scroll_area->verticalScrollBar()->setValue(inside_messages_scroll_area->verticalScrollBar()->maximum());

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

void RoomInsideWidget::slot_clicked_clip_button() {
   QFileInfo file(QFileDialog::getOpenFileName());
   emit clicked_clip_button(file.fileName());
}

void RoomInsideWidget::slot_open_file_button(const MessageWidget& sender_) {
    if (sender_.is_media) {
        emit signal_open_file_button(sender_.file_name, sender_.author);
    }
}

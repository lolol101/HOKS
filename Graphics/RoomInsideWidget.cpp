#include "RoomInsideWidget.h"
#include "ui_RoomInsideWidget.h"

RoomInsideWidget::RoomInsideWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoomInsideWidget)
{
    ui->setupUi(this);
}

RoomInsideWidget::RoomInsideWidget(const RoomIconWidget *room_iconm, QList<QString> *room_messages) {
    room_inside_ = new QWidget(this);
    message_line = new QTextEdit(room_inside_);
    room_messages_ = room_messages;
}

RoomInsideWidget::~RoomInsideWidget()
{
    delete ui;
}

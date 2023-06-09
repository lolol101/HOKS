#include "RoomIconWidget.h"
#include "ui_RoomIconWidget.h"

RoomIconWidget::RoomIconWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoomIconWidget)
{
    ui->setupUi(this);
}

RoomIconWidget::RoomIconWidget(const QString &room_name) {
    room_name_ = room_name;
    room_icon_ = new QPushButton(this);
    room_icon_->setText(room_name);
    room_icon_->setFixedSize(246, 80);
    room_icon_->setStyleSheet(current_style.room_icon);
    connect(this->room_icon_, &QPushButton::clicked, this, &RoomIconWidget::slot_clicked);
}

void RoomIconWidget::slot_clicked() {
    emit clicked_icon();
}

RoomIconWidget::~RoomIconWidget()
{
    delete ui;
}

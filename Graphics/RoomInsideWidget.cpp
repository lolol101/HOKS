#include "RoomInsideWidget.h"
#include "ui_RoomInsideWidget.h"

RoomInsideWidget::RoomInsideWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoomInsideWidget)
{
    ui->setupUi(this);
}

RoomInsideWidget::RoomInsideWidget(const RoomIconWidget *room_icon) {
    room_inside_ = new QWidget(this);
}

RoomInsideWidget::~RoomInsideWidget()
{
    delete ui;
}

#include "RoomIconWidget.h"
#include "ui_RoomIconWidget.h"

RoomIconWidget::RoomIconWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoomIconWidget)
{
    ui->setupUi(this);
}

RoomIconWidget::~RoomIconWidget()
{
    delete ui;
}

#include "Room.h"
#include "ui_Room.h"

Room::Room(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Room)
{
    ui->setupUi(this);
}

Room::~Room()
{
    delete ui;
}

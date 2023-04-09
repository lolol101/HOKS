#include "NewRoomWidget.h"
#include "ui_NewRoomWidget.h"

NewRoomWidget::NewRoomWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewRoomWidget)
{
    ui->setupUi(this);
}

QCheckBox &NewRoomWidget::make_checkbox_for_person(const QString &person_name) {

}

void NewRoomWidget::show_checkbox_for_person(QCheckBox& person) {

}

NewRoomWidget::~NewRoomWidget()
{
    delete ui;
}

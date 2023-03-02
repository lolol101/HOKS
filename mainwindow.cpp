#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    qApp->setStyleSheet("QMainWindow { background-color: #111111; }"
                        "QPushButton {  border: 1px solid; border-radius: 19px; border-color: #666666;  color: #ffffff;  background-color: #111111; }"
                        "QPushButton:hover{  border-color: #777777; }"
                        "QPushButton:pressed:hover {  background-color: #777777;     color: #ffffff; }"
                        "QLineEdit { color: #a4a4a4;  background-color: #333333;  border-radius: 12px;  padding: 6px; }"
                        "QLabel { color: #a4a4a4; }"
                        "QMessageBox { background-color: #111111; } "
                        "QMessageBox QPushButton { background-color: #111111; } ");
    ui->setupUi(this);
    connect(ui->Log_in_button, SIGNAL(clicked()), this, SLOT(push_on_button_log_in()));
    ui->Main_label->setStyleSheet("color: #ffffff");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::push_on_button_log_in() {
    QString user_name = ui->Name_line->text();
    QString user_password = ui->Password_line->text();
    QString user_data = "User name: '" + user_name + "'\n";
    user_data += ("User password: '" + user_password + "'\n");
    QMessageBox::information(this, "Title", user_data);
}

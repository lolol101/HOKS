#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    make_window_skillet();
}

void MainWindow::show_main_window() {
    MainWindow* m;
    m = new MainWindow();
    m->show();
}

void MainWindow::make_window_skillet() {
    this->move(170, 20);
    this->setFixedSize(1000, 700);

    QString default_style = current_style.button_standard +
            current_style.main_window +
            current_style.line_edit_standard +
            current_style.label_standard +
            current_style.message_box_standard;
    qApp->setStyleSheet(default_style);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


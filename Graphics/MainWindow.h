#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <appstyle.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    style_table current_style;

    void make_window_skillet();
    void show_main_window();

    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

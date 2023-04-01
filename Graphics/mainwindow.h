#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <appstyle.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QWidget *authorization_widget;
    QWidget *registration_widget;

    QLabel *HOKS_authorization_label;
    QLabel *login_authorization_label;
    QLabel *password_authorization_label;

    QLabel *email_registration_label;
    QLabel *first_name_registration_label;
    QLabel *last_name_registration_label;

    QLineEdit *login_authorization_line_edit;
    QLineEdit *password_authorization_line_edit;

    QLineEdit *email_registration_line_edit;
    QLineEdit *first_name_registration_line_edit;
    QLineEdit *last_name_registration_line_edit;

    QPushButton *authorization_button;
    QPushButton *registration_button;

    style_table current_style{};

    void show_authorization();
    void show_registration();
    void show_main_window();
    void recover_registration_window_view();

private slots:
    void push_on_authorization_button();
    void push_on_registration_button();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

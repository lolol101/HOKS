#ifndef APPGRAPHIC_H
#define APPGRAPHIC_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <appstyle.h>

QT_BEGIN_NAMESPACE
namespace Ui { class appGraphic; }
QT_END_NAMESPACE

class appGraphic : public QMainWindow
{
    Q_OBJECT

public:
    appGraphic(QWidget *parent = nullptr);
    ~appGraphic();

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
    QPushButton *back_to_authorization_button;

    style_table current_style{};

    void make_window_skillet();
    void make_authorization_elements();
    void make_registration_elements();

    void show_main_window();
    void show_authorization();
    void show_registration();
    void recover_registration_window_view();

    void change_user_registration_label(QLabel *registration_label, const QString &new_text, const style_table &current_style);

private slots:
    void push_on_authorization_button();
    void push_on_registration_button();
    void push_on_back_to_authorization_button();

signals:
    void user_authorization_signal(const QString &user_login, const QString &user_password);
    void user_registration_signal(const QString &user_login,
                           const QString &user_password,
                           const QString &user_email,
                           const QString &user_first_name,
                           const QString &user_last_name);


private:
    Ui::appGraphic *ui;
};
#endif // APPGRAPHIC_H

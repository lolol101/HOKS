#ifndef authorizationWindow_H
#define authorizationWindow_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <appstyle.h>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class authorizationWindow; }
QT_END_NAMESPACE

class authorizationWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::authorizationWindow *ui;

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

    style_table current_style;

    void make_window_skillet();
    void make_authorization_elements();
    void make_registration_elements();

    void hide_authorization();
    void hide_registration();

public:
    authorizationWindow(QWidget *parent = nullptr);
    ~authorizationWindow();

    void show_authorization();
    void show_registration();

    void show_login_input_error(const QString &new_text);
    void show_password_input_error(const QString &new_text);
    void show_email_input_error(const QString &new_text);
    void show_first_name_input_error(const QString &new_text);
    void show_last_name_input_error(const QString &new_text);

    void recover_registration_window_view();

    void clear_login_input();
    void clear_password_input();
    void clear_email_input();
    void clear_first_name_input();
    void clear_last_name_input();

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
    void open_main_window();

};
#endif // authorizationWindow_H

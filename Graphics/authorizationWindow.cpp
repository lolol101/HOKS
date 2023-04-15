#include "authorizationWindow.h"
#include "ui_authorizationWindow.h"
#include <appstyle.h>
#include <QMessageBox>
#include <QString>
#include <vector>
#include <string>
#include <algorithm>
#include <MainWindow.h>

authorizationWindow::authorizationWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::authorizationWindow)
{
    make_window_skillet();
    make_authorization_elements();
    make_registration_elements();
    show_authorization();
}

void authorizationWindow::make_window_skillet() {
    this->move(400, 180);
    this->setFixedSize(500, 460);

    QString default_style = current_style.button_standard +
            current_style.main_window +
            current_style.line_edit_standard +
            current_style.label_standard +
            current_style.message_box_standard;
    qApp->setStyleSheet(default_style);
    ui->setupUi(this);
}

void authorizationWindow::make_authorization_elements() {
    authorization_widget = new QWidget(this);
    authorization_widget->setGeometry(0, 0, 500, 279);
    HOKS_authorization_label = new QLabel("Добро пожаловать в HOKS!", authorization_widget);
    HOKS_authorization_label->setStyleSheet(current_style.authorization_label);
    HOKS_authorization_label->setGeometry(0, 70, 500, 40);

    // Логин
    login_authorization_label = new QLabel("Логин", authorization_widget);
    login_authorization_label->setStyleSheet(current_style.left_alignment_label);
    login_authorization_label->setGeometry(130, 158, 240, 16);

    login_authorization_line_edit = new QLineEdit(authorization_widget);
    login_authorization_line_edit->setGeometry(130, 178, 240, 30);

    // Пароль
    password_authorization_label = new QLabel("Пароль", authorization_widget);
    password_authorization_label->setStyleSheet(current_style.left_alignment_label);
    password_authorization_label->setGeometry(130, 229, 240, 16);

    password_authorization_line_edit = new QLineEdit(authorization_widget);
    password_authorization_line_edit->setGeometry(130, 249, 240, 30);

    // Кнопка авторизации
    authorization_button = new QPushButton(this);
    authorization_button->setGeometry(200, 330, 100, 40);
    authorization_button->setText("Войти");

    hide_authorization();

    connect(authorization_button, &QPushButton::clicked, this, & authorizationWindow::push_on_authorization_button);
}

void authorizationWindow::make_registration_elements() {
    authorization_button->hide();

    registration_widget = new QWidget(this);
    registration_widget->setGeometry(0, 279, 500, 682);

    // E-mail
    email_registration_label = new QLabel("E-mail", registration_widget);
    email_registration_label->setStyleSheet(current_style.left_alignment_label);
    email_registration_label->setGeometry(130, 21, 240, 16);

    email_registration_line_edit = new QLineEdit(registration_widget);
    email_registration_line_edit->setGeometry(130, 41, 240, 30);

    // Имя
    first_name_registration_label = new QLabel("Имя", registration_widget);
    first_name_registration_label->setStyleSheet(current_style.left_alignment_label);
    first_name_registration_label->setGeometry(130, 92, 240, 16);

    first_name_registration_line_edit = new QLineEdit(registration_widget);
    first_name_registration_line_edit->setGeometry(130, 112, 240, 30);

    // Фамилия
    last_name_registration_label = new QLabel("Фамилия", registration_widget);
    last_name_registration_label->setStyleSheet(current_style.left_alignment_label);
    last_name_registration_label->setGeometry(130, 163, 240, 16);

    last_name_registration_line_edit = new QLineEdit(registration_widget);
    last_name_registration_line_edit->setGeometry(130, 183, 240, 30);

    // Кнопка регистрации:
    registration_button = new QPushButton(registration_widget);
    registration_button->setGeometry(160, 264, 180, 40);
    registration_button->setText("Зарегистрироваться");

    // Кнорка "назад"
    back_to_authorization_button = new QPushButton(this);
    back_to_authorization_button->setGeometry(20, 20, 24, 24);
    back_to_authorization_button->setStyleSheet(current_style.back_to_authorization_button);

    hide_registration();

    connect(back_to_authorization_button, &QPushButton::clicked, this, &authorizationWindow::push_on_back_to_authorization_button);
    connect(registration_button, &QPushButton::clicked, this, &authorizationWindow::push_on_registration_button);
}

void authorizationWindow::show_authorization() {
    this->setWindowTitle("Вход в HOKS");

    this->move(400, 180);
    this->setFixedSize(500, 460);

    authorization_widget->show();
    authorization_button->show();
}

void authorizationWindow::show_registration() {
    this->setWindowTitle("Регистрация в HOKS");

    this->move(400, 40);
    this->setFixedSize(500, 682);

    authorization_button->hide();
    registration_widget->show();
    registration_button->show();
    back_to_authorization_button->show();
}

void authorizationWindow::hide_authorization() {
    authorization_widget->hide();
    authorization_button->hide();
}

void authorizationWindow::hide_registration() {
    registration_widget->hide();
    registration_button->hide();
    back_to_authorization_button->hide();
}

void authorizationWindow::recover_registration_window_view() {
    login_authorization_label->setStyleSheet(current_style.label_standard);
    password_authorization_label->setStyleSheet(current_style.label_standard);
    email_registration_label->setStyleSheet(current_style.label_standard);
    first_name_registration_label->setStyleSheet(current_style.label_standard);
    last_name_registration_label->setStyleSheet(current_style.label_standard);

    login_authorization_label->setText("Логин");
    password_authorization_label->setText("Пароль");
    email_registration_label->setText("E-mail");
    first_name_registration_label->setText("Имя");
    last_name_registration_label->setText("Фамилия");
}

void authorizationWindow::push_on_authorization_button() {
    QString user_login = login_authorization_line_edit->text();
    QString user_password = password_authorization_line_edit->text();
    emit user_authorization_signal(user_login, user_password);

//    if (user_login == "ilia" && user_password == "123") { // Пользователь есть в
//            show_main_window();
//        } else { // Пользователя в БД нет
//            QMessageBox::StandardButton registration_dialog_box;
//            registration_dialog_box = QMessageBox::question(nullptr,
//            "Зарегистрироваться?",
//            "Пользователь с введёнными данными не найден. \nХотите зарегистрироваться?",
//            QMessageBox::Yes | QMessageBox::No);
//                if (registration_dialog_box == QMessageBox::Yes) {
//                    show_registration();
//                }
//        }
}

void authorizationWindow::push_on_registration_button() {
    QString user_login = login_authorization_line_edit->text();
    QString user_password = password_authorization_line_edit->text();
    QString user_email = email_registration_line_edit->text();
    QString user_first_name = first_name_registration_line_edit->text();
    QString user_last_name = last_name_registration_line_edit->text();
    emit user_registration_signal(user_login, user_password, user_email, user_first_name, user_last_name);

//    std::vector<QString> all_users = {"ilia", "nikita", "igor"};
//    bool is_user_data_correct = true;
//    // Такой пользователь уже существует
//    if (std::find(all_users.begin(), all_users.end(), user_login) != all_users.end()) {

//        show_login_input_error("Логин затят");
//        is_user_data_correct = false;
//    } if (user_password.size() < 3) { // Пароль не является безопасным
//        show_password_input_error("Пароль слишком короткий");
//        is_user_data_correct = false;
//    } if (user_email.indexOf("@") == -1) { // E-mail некорректен
//        show_email_input_error("E-mail указан неверно");
//        is_user_data_correct = false;
//    } if (user_first_name == "") { // Имя пустое
//        show_first_name_input_error("Имя не может быть пустым");
//        is_user_data_correct = false;
//    } if (user_last_name == "") { // Фамилия пустая
//        show_last_name_input_error("Фамилия не может быть пустой");
//        is_user_data_correct = false;
//    } if (is_user_data_correct) { // Пользователь успешно зарегистрировался
//        show_main_window();
//    }
}

void authorizationWindow::push_on_back_to_authorization_button() {
    hide_registration();
    show_authorization();
    recover_registration_window_view();
}

void authorizationWindow::show_login_input_error(const QString &new_text) {
    login_authorization_label->setText(new_text);
    login_authorization_label->setStyleSheet(current_style.wrong_registration_data_label);
}

void authorizationWindow::show_password_input_error(const QString &new_text) {
    password_authorization_label->setText(new_text);
    password_authorization_label->setStyleSheet(current_style.wrong_registration_data_label);
}

void authorizationWindow::show_email_input_error(const QString &new_text) {
    email_registration_label->setText(new_text);
    email_registration_label->setStyleSheet(current_style.wrong_registration_data_label);
}

void authorizationWindow::show_first_name_input_error(const QString &new_text) {
    first_name_registration_label->setText(new_text);
    first_name_registration_label->setStyleSheet(current_style.wrong_registration_data_label);
}

void authorizationWindow::show_last_name_input_error(const QString &new_text) {
    last_name_registration_label->setText(new_text);
    last_name_registration_label->setStyleSheet(current_style.wrong_registration_data_label);
}

void authorizationWindow::clear_login_input() {
    login_authorization_line_edit->clear();
}

void authorizationWindow::clear_password_input() {
    password_authorization_line_edit->clear();
}

void authorizationWindow::clear_email_input() {
    email_registration_line_edit->clear();
}

void authorizationWindow::clear_first_name_input() {
    first_name_registration_line_edit->clear();
}

void authorizationWindow::clear_last_name_input() {
    last_name_registration_line_edit->clear();
}

authorizationWindow::~ authorizationWindow() {
    delete ui;
}

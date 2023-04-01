#ifndef APPSTYLE_H
#define APPSTYLE_H
#include <QString>
#include <unordered_map>
#include <string>

class style_table {
public:
    std::unordered_map<std::string, QString> colors = {
            {"main_window_background_color",                    "#111111;"},
            {"button_standard_background_color",                "#111111;"},
            {"button_standard_border_color",                    "#666666;"},
            {"button_standard_color",                           "#ffffff;"},
            {"button_standard_border_color_hover",              "#777777;"},
            {"button_standard_background_color_pressed_hover",  "#777777;"},
            {"button_standard_color_pressed_hover",             "#ffffff;"},
            {"line_edit_standard_color",                        "#a4a4a4;"},
            {"line_edit_standard_background_color",             "#333333;"},
            {"label_standard_color",                            "#a4a4a4;"},
            {"message_box_standard_background_color",           "#111111;"},
            {"authorization_label_color",                       "#ffffff;"},
            {"wrong_registration_data_label_color",             "#ff7373;"},
    };

    QString main_window =
            "QMainWindow {"
                "background-color: " + colors["main_window_background_color"] +
            "}";
    QString button_standard =
            "QPushButton {"
                "background-color: " + colors["button_standard_background_color"] +
                "border: 1px solid;"
                "border-radius: 19px;"
                "border-color: " + colors["button_standard_border_color"] +
                "color: " + colors["button_standard_color"] +
                "padding: 10px 10px;"
            "}"
            "QPushButton:hover {"
                "border-color: " + colors["button_standard_border_color_hover"] +
            "}"
            "QPushButton:pressed:hover {"
                "background-color: " + colors["button_standard_background_color_pressed_hover"] +
                "color: " + colors["button_standard_color_pressed_hover"] +
            "}";
    QString line_edit_standard =
            "QLineEdit {"
                "color: " + colors["line_edit_standard_color"] +
                "background-color: " + colors["line_edit_standard_background_color"] +
                "border-radius: 12px;"
                "padding: 6px;"
            "}";
    QString label_standard =
            "QLabel {"
                "color: " + colors["label_standard_color"] +
            "}";
    QString message_box_standard =
            "QMessageBox {"
                "background-color: " + colors["message_box_standard_background_color"] +
            "}";
    QString authorization_label =
            "font-family: Geneva;"
            "font-size: 24px;"
            "color: " + colors["authorization_label_color"] +
            "qproperty-alignment: AlignCenter;";
    QString left_alignment_label =
            "qproperty-alignment: AlignLeft;";
    QString wrong_registration_data_label =
            "color: " + colors["wrong_registration_data_label_color"];
};

#endif // APPSTYLE_H

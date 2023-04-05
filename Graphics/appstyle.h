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
            {"line_edit_standard_color",                        "#a4a4a4;"},
            {"line_edit_standard_background_color",             "#333333;"},
            {"label_standard_color",                            "#a4a4a4;"},
            {"message_box_standard_background_color",           "#111111;"},
            {"authorization_label_color",                       "#ffffff;"},
            {"wrong_registration_data_label_color",             "#ff7373;"},
            {"back_to_authorization_button_pressed_hover",      "#111111;"},
            {"room_icon_background_color",                      "#161616;"},
            {"room_icon_border_color",                          "#606060;"},
            {"room_inside_background_color",                    "#111111;"},
            {"rooms_space_widget_background_color",             "#111111;"}
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
    QString back_to_authorization_button =
            "QPushButton {"
                "border: 0px solid;"
            "}"
            "QPushButton:pressed:hover {"
                "background-color: " + colors["back_to_authorization_button_pressed_hover"] +
            "}"
            "QPushButton {"
                "background-image: url(:/icons/icons/back_button_default.png);"
            "}"
            "QPushButton:hover {"
                "background-image: url(:/icons/icons/back_button_hovered.png);"
            "}"
            "QPushButton:pressed:hover {"
                "background-image: url(:/icons/icons/back_button_hovered_pushed.png);"
            "}";
    QString room_icon =
            "QPushButton {"
                "background-color: "  + colors["room_icon_background_color"] +
                "border: 1px solid;"
                "border-radius: 25px;"
                "border-color: "  + colors["room_icon_border_color"] +
             "}";
    QString room_inside =
            "QWidget {"
                "background-color: " + colors["room_inside_background_color"] +
            "}";
    QString rooms_space_scroll_bar = "";
    QString rooms_space_widget =
            "QWidget {"
                "background-color: " + colors["rooms_space_widget_background_color"] +
            "}";
};

#endif // APPSTYLE_H

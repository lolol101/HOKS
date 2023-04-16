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
            {"room_icon_background_color",                      "#111111;"},
            {"room_icon_border_color",                          "#606060;"},
            {"room_inside_background_color",                    "#111111;"},
            {"rooms_space_widget_background_color",             "#111111;"},
            {"message_line_background_color",                   "#111111;"},
            {"message_line_color",                              "#f8f7f8;"},
            {"message_line_border_color",                       "#606060;"}
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
                "border: 0px solid;"
                "color: " + colors["line_edit_standard_color"] +
                "background-color: " + colors["line_edit_standard_background_color"] +
                "border-radius: 12px;"
                "padding: 6px;"
                "font-size: 15px;"
            "}";
    QString label_standard =
            "QLabel {"
                "color: " + colors["label_standard_color"] +
            "}";
    QString message_box_standard =
            "QMessageBox {"
                "background-color: " + colors["message_box_standard_background_color"] +
            "}";

    QString scroll_rooms_widget =
            "QWidget {"
                "border-right: 0px solid;"
                "background-color: " + colors["room_inside_background_color"] +
            "}";

    QString scroll_bar_standard =
            "QWidget {"
                "background-color: " + colors["room_inside_background_color"] +
            "}"
            "QScrollBar {"
                "background-color: rgba(17, 17, 17, 0);"
                "width: 8px;"
            "}"
            "QScrollBar::handle {"
                "border-radius: 4px;"
                "background-color: rgba(96, 96, 96, 0.6);"
            "}"
            "QScrollBar:handle:hover {"
                "background-color: rgba(96, 96, 96, 0.8);"
            "}"
            "QScrollBar:handle:pressed:hover {"
                "background-color: rgba(96, 96, 96, 0.8);"
            "}"

            "QScrollBar::add-page,"
            "QScrollBar::sub-page,"
            "QScrollBar::add-line,"
            "QScrollBar::sub-line {"
                "border: none;"
                "background: none;"
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
                "background-color: " + colors["main_window_background_color"] +
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
            "background-color: "  + colors["room_icon_background_color"] +
            "border: 0px solid;"
            "border-radius: 0px;"
            "border-bottom: 1px solid #606060;";
    QString inside_messages_widget =
            "QWidget {"
                "border: 0px solid;"
                "background-color: " + colors["room_inside_background_color"] +
            "}";

    QString rooms_space_widget =
            "QWidget {"
                "border: 0px solid;"
                "background-color: " + colors["rooms_space_widget_background_color"] +
            "}";
    QString users_search_line_edit =
            "border: 0px;";
    QString new_room_name_line_edit =
            "border: 0px;";
    QString inside_message_line =
                "background-color: " + colors["message_line_background_color"] +
                "color: " + colors["message_line_color"] +
                "border: 0px solid;"
                "padding: 11px 15px;"
                "font-size: 15px;";
    QString inside_room_name_widget =
                "border-left: 0px solid #606060;"
                "background-color: #111111;"
                "border-bottom: 1px solid #606060;";
    QString messages_widget =
                "background-color: #2c2c2c;"
                "border-radius: 15px;"
                "border: 0px solid;";
    QString messages_label =
            "QLabel {"
                "color: #ffffff;"
                "font-family: Geneva;"
                "font-size: 14px;"
                "qproperty-alignment: AlignCenter;"
            "}";
    QString send_message_button =
            "QPushButton {"
                "border: 0px solid;"
            "}"
            "QPushButton:pressed:hover {"
                "background-color: " + colors["main_window_background_color"] +
            "}"
            "QPushButton {"
                "background-image: url(:/icons/icons/send_message_button.png);"
            "}"
            "QPushButton:hover {"
                "background-image: url(:/icons/icons/send_message_button_pushed.png);"
            "}"
            "QPushButton:pressed:hover {"
                "background-image: url(:/icons/icons/send_message_button_pushed.png);"
            "}";
    QString create_new_room_widget =
            "QWidget {"
                "border: 0px;"
                "border-top: 1px solid #606060;"
                "background-color: #555555;"
            "}";

    QString select_people_widget =
            "QWidget {"
                "background-color: #111111;"
            "}";
    QString person_checkbox =
            "QCheckBox {"
                "background-color: transparent;"
                "color: #a4a4a4;"
                "font-size: 19px;"
                "border: 0px;"
            "}"
            "QCheckBox::indicator {"
                "width: 16px;"
                "height: 16px;"
                "border-radius: 8px;"
                "border: 1px solid #a4a4a4;"
            "}"
            "QCheckBox::indicator:unchecked {"
            "}"
            "QCheckBox::indicator:checked {"
                "background-color: #a4a4a4;"
            "}";
    QString person_checkbox_widget =
            "font-size: 19px;"
            "border-bottom: 1px solid #606060;";
    QString left_widget =
        "QWidget {"
            "border-right: 1px solid #606060;"
        "}"
        "QScrollBar {"
            "border-right: 0px solid;"
            "background-color: rgba(17, 17, 17, 0);"
            "width: 8px;"
        "}"
        "QScrollBar::handle {"
            "border-right: 0px solid;"
            "border-radius: 3px;"
            "background-color: rgba(96, 96, 96, 0.6);"
        "}"
        "QScrollBar:handle:hover {"
            "border-right: 0px solid;"
            "background-color: rgba(96, 96, 96, 0.8);"
        "}"
        "QScrollBar:handle:pressed:hover {"
            "border-right: 0px solid;"
            "background-color: rgba(96, 96, 96, 0.8);"
        "}"

        "QScrollBar::add-page,"
        "QScrollBar::sub-page,"
        "QScrollBar::add-line,"
        "QScrollBar::sub-line {"
            "border-right: 0px solid;"
            "background: none;"
        "}";
    QString top_widget =
            "border-right: 0px;"
            "background-color: #111111;";

    QString button_create_new_room =
            "QPushButton {"
                "border: 1px solid #606060;"
                "font-size: 17px;"
                "border-radius: 15px;"
                "padding-top: 3px;"
                "padding-bottom: 5px;"
                "padding-left: 3px;"
                "padding-right: 3px;"
            "}"
             "QPushButton:hover {"
                "border-color: #777777;"
            "}"
            "QPushButton:pressed:hover {"
                "background-color: #777777;"
            "}";
    QString create_new_room_bottom_widget =
            "border-top: 1px solid #606060;";
    QString create_new_room_top_widget =
            "border-bottom: 1px solid #606060;";

    QString inside_room_name_label =
            "border: 0px solid;"
            "font-size: 18px;";
    QString message_line_area_widget =
            "border: 0px;"
            "border-top: 1px solid #606060;";
};

#endif // APPSTYLE_H

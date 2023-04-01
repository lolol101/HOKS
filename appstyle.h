#ifndef APPSTYLE_H
#define APPSTYLE_H
#include <QString>

class style_table {
public:
    QString main_window =
            "QMainWindow {"
                "background-color: #111111;"
            "}";
    QString button_standard =
            "QPushButton {"
                "background-color: #111111;"
                "border: 1px solid;"
                "border-radius: 19px;"
                "border-color: #666666;"
                "color: #ffffff;"
                "padding: 10px 10px;"
            "}"
            "QPushButton:hover {"
                "border-color: #777777;"
            "}"
            "QPushButton:pressed:hover {"
                "background-color: #777777;"
                "color: #ffffff;"
            "}";
    QString line_edit_standard =
            "QLineEdit {"
                "color: #a4a4a4;"
                "background-color: #333333;"
                "border-radius: 12px;"
                "padding: 6px;"
            "}";
    QString label_standard =
            "QLabel {"
                "color: #a4a4a4;"
            "}";
    QString message_box_standard =
            "QMessageBox {"
                "background-color: #111111;"
            "}";
    QString authorization_label =
            "font-family: Geneva;"
            "font-size: 24px;"
            "color: #ffffff;"
            "qproperty-alignment: AlignCenter;";
    QString left_alignment_label =
            "qproperty-alignment: AlignLeft;";
    QString wrong_registration_data_label =
            "color: #ff7373;";
};

#endif // APPSTYLE_H

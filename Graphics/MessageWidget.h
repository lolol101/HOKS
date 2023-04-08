#ifndef MESSAGEWIDGET_H
#define MESSAGEWIDGET_H

#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class MessageWidget;
}

class MessageWidget : public QWidget {
public:
    MessageWidget(QWidget *parent = nullptr) : QWidget(parent) {}

    void mousePressEvent(QMouseEvent *event) override;
};

#endif // MESSAGEWIDGET_H

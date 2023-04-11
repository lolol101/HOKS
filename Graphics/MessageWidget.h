#ifndef MESSAGEWIDGET_H
#define MESSAGEWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QDebug>

namespace Ui {
class MessageWidget;
}

class MessageWidget : public QWidget {
public:
    MessageWidget(QWidget *parent = nullptr) : QWidget(parent) {}

    void mousePressEvent(QMouseEvent *event) override;
};

#endif // MESSAGEWIDGET_H

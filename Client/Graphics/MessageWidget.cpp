#include "MessageWidget.h"

void MessageWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        qDebug() << "Right mouse clicked";
    }

    QWidget::mousePressEvent(event);
}

#ifndef MESSAGEWIDGET_H
#define MESSAGEWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QDebug>
#include <QObject>
#include <QPushButton>

namespace Ui {
class MessageWidget;
}

class MessageWidget : public QWidget {

    Q_OBJECT

public:

    MessageWidget(QWidget* parent = nullptr) : QWidget(parent) {
    }

    void connect_signals_to_slots() {connect(open_file_button, &QPushButton::clicked, this, &MessageWidget::slot_clicked_open_button);}

    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::RightButton) {
            qDebug() << "Right mouse clicked";
        }

        QWidget::mousePressEvent(event);
    }

    QPushButton *sent_file_icon;
    QPushButton *open_file_button;

    QString file_name;
    QString author;
    bool is_media;

    signals:
        void signal_clicked_open_button(const MessageWidget& p);
    public slots:
        void slot_clicked_open_button();

};

#endif // MESSAGEWIDGET_H

#ifndef MESSAGELINE_H
#define MESSAGELINE_H

#include <QWidget>
#include <QTextEdit>
#include <QKeyEvent>

namespace Ui {
class MessageLine;
}

class MessageLine : public QTextEdit
{
    Q_OBJECT

public:
    explicit MessageLine(QWidget *parent = nullptr);

    void keyPressEvent(QKeyEvent *event) override;

    ~MessageLine();

signals:
    void push_on_enter_to_send_signal();

private:
    Ui::MessageLine *ui;
};

#endif // MESSAGELINE_H

#include "MessageLine.h"
#include "ui_MessageLine.h"

MessageLine::MessageLine(QWidget *parent) :
    QTextEdit(parent),
    ui(new Ui::MessageLine)
{
    ui->setupUi(this);
}

void MessageLine::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return) {
        emit push_on_enter_to_send_signal();
    }
    else {
        QTextEdit::keyPressEvent(event);
    }
 }

MessageLine::~MessageLine()
{
    delete ui;
}

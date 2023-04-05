#ifndef ROOMINSIDEWIDGET_H
#define ROOMINSIDEWIDGET_H

#include <QWidget>

namespace Ui {
class RoomInsideWidget;
}

class RoomInsideWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RoomInsideWidget(QWidget *parent = nullptr);
    ~RoomInsideWidget();

private:
    Ui::RoomInsideWidget *ui;
};

#endif // ROOMINSIDEWIDGET_H

#ifndef ROOMICONWIDGET_H
#define ROOMICONWIDGET_H

#include <QWidget>

namespace Ui {
class RoomIconWidget;
}

class RoomIconWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RoomIconWidget(QWidget *parent = nullptr);
    ~RoomIconWidget();

private:
    Ui::RoomIconWidget *ui;
};

#endif // ROOMICONWIDGET_H

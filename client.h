#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QByteArray>
#include <QTcpSocket>
#include <unordered_map>

QT_BEGIN_NAMESPACE
namespace Ui { class Client; }
QT_END_NAMESPACE

enum Command { gotMessageFromClient, gotMessageFromServer };

class Client : public QMainWindow {
    Q_OBJECT
private:
    QTcpSocket* socket;
    quint16 blockSize;
    Ui::Client *ui;

    QByteArray makeByteMessage(const Command &command, const QString& message);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();

public:
    Client(QWidget *parent = nullptr);
    ~Client();

public slots:
    void slotReadyRead();
//    void slotDisconnected();
};
#endif // CLIENT_H

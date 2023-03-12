#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <QTcpServer>
#include <QTcpSocket>
#include <unordered_map>

enum Command { gotMessageFromClient, gotMessageFromServer };

class Server : public QTcpServer
{
    Q_OBJECT
private:
    std::vector<QTcpSocket*> clients;
    std::unordered_map<QTcpSocket*, quint16> clientsMsgSize;
    QByteArray makeByteMessage(const Command& command, const QString& message);

public:
    Server();

public slots:
    void newConnection();
    void slotReadyRead();
};

#endif // SERVER_H

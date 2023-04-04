#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <unordered_map>
#include <database/database.h>
#include "Commands.h"

class Server : public QTcpServer {
    Q_OBJECT

private:
    db_space::Database data_base;
    std::vector<QTcpSocket*> clients;
    std::unordered_map<QTcpSocket*, quint16> clients_msg_size;
    QByteArray make_byte_message(const Command& command, const QString& message);

public:
    Server();
    void start();

public slots:
    void new_connection();
    void slot_ready_read();
};

#endif // SERVER_H

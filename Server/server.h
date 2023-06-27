#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <QMap>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <database/database.h>
#include "Commands.h"

class Server : public QTcpServer {
    Q_OBJECT

private:
    db_space::Database data_base;

    QMap<QString, QTcpSocket*> sockets;
    QMap<QTcpSocket*, quint16> clients_msg_size;

    template<class T>
    QByteArray make_byte_message(const Command &command, const QVector<T>& arguments);
    QByteArray make_byte_message(const Command &command, const QString& file_name, const QByteArray& bytes);

public:
    Server();
    void start();

signals:
    void room_created(const QString& room_name, int id);

public slots:
    void new_connection();
    void slot_ready_read();
};

#endif // SERVER_H

#include "server.h"

QByteArray Server::makeByteMessage(const Command &command, const QString& message)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0 << quint8(command) << message;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    return block;
}

Server::Server() {
    if (this->listen(QHostAddress("192.168.0.100"), 1101)) {
        std::cout << "Start\n";
        connect(this, &QTcpServer::newConnection, this, &Server::newConnection);
    }
    else
        std::cout << "Error\n";
}

void Server::newConnection() {
    QTcpSocket* socket = this->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    clients.emplace_back(socket);
    socket->write(makeByteMessage(Command::gotMessageFromServer, "Connected Waltahhh."));
}


void Server::slotReadyRead() {
    QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_15);
    if (in.status() == QDataStream::Ok) {
        while (true) {
            if (clientsMsgSize[socket] == 0) {
                if (socket->bytesAvailable() < 2)
                    break;
                in >> clientsMsgSize[socket];
            }
            if (socket->bytesAvailable() < clientsMsgSize[socket])
                break;
            clientsMsgSize[socket] = 0;
            quint8 command;
            in >> command;
            switch (command) {
                case Command::gotMessageFromClient: {
                    QString message;
                    in >> message;
                    for (auto& obj : clients) {
                        if (obj != socket) {
                            obj->write(makeByteMessage(Command::gotMessageFromServer, message));
                        }
                    }
                    break;
                }
            }
            break;
        }
    }
}


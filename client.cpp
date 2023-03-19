#include "client.h"
#include "ui_client.h"

QByteArray Client::makeByteMessage(const Command &command, const QString& message)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0 << quint8(command) << message;
    return block;
}

Client::Client(QWidget *parent) : QMainWindow(parent), ui(new Ui::Client) {
    socket = new QTcpSocket;
    connect(socket, &QTcpSocket::readyRead, this, &Client::slotReadyRead);
    blockSize = 0;
    ui->setupUi(this);
}

void Client::slotReadyRead() { // TODO different commands by enum!
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_4);
    if (in.status() == QDataStream::Ok) {
        while (true) {
            if (blockSize == 0) {
                if (socket->bytesAvailable() < 2)
                    break;
                in >> blockSize;
            }
            if (socket->bytesAvailable() < blockSize)
                break;
            blockSize = 0;
            quint8 command;
            in >> command;
            switch (command) {
                case Command::gotMessageFromServer: {
                    QString text;
                    in >> text;
                    ui->textEdit->append(text);
                    break;
                }
            }
            break;
        }
    }

}

Client::~Client() {
    delete ui;
}

void Client::on_pushButton_clicked() {
    socket->connectToHost("192.168.0.100", 1101); // it's not right port
}

void Client::on_pushButton_3_clicked() {
    socket->write(makeByteMessage(Command::gotMessageFromClient, ui->lineEdit->text()));
    ui->textEdit->append("me: " + ui->lineEdit->text());
    ui->lineEdit->clear();
}


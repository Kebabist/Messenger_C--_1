#include "Server.h"


void Server::incomingConnection(qintptr socketDescriptor)
{
    std::cout << "Incoming connection from client" << std::endl;

    QTcpSocket *socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);
    clients.append(socket);

    connect(socket, &QTcpSocket::disconnected, this, &Server::disconnected);
    connect(socket, &QTcpSocket::readyRead, this, &Server::readyRead);
}
void Server::disconnected()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    std::cout << "Client disconnected" << std::endl;
    clients.removeOne(socket);
    socket->deleteLater();
}

void Server::readyRead()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    QByteArray data = socket->readAll();
    std::cout << "Received message: " <<data.constData() << std::endl;

    // Echo the message back to all connected clients
    for (QTcpSocket *client : clients) {
        if (client != socket) {
            client->write(data);
        }
    }
}

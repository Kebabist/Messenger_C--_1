#ifndef SERVER_H
#define SERVER_H
#include <QtNetwork>
#include <QCoreApplication>
#include <iostream>
#include <QWidget>

class Server : public QTcpServer
{
    Q_OBJECT   
private:
    QList<QTcpSocket*> clients;

public:
    Server(QObject *parent = nullptr) : QTcpServer(parent)
    {
        std::cout << "Server listening on port " << serverPort() << std::endl;
    }

protected:
    void incomingConnection(qintptr socketDescriptor) override;

public slots:
    void disconnected();
    void readyRead();
signals:
};

#endif // SERVER_H

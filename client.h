#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QWidget>

class Client
{
    QString username;
    QString password;
    QString firstname;
    QString lastname;
    QString token;
public:
    Client(QString, QString , QString , QString);
    void Singup();
    void Login();
};

#endif // CLIENT_H

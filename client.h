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
  
    QPair<QString, QString> Signup();
    void Login(QString, QString);
    void Logout(QString, QString);

    //getter Merhods
    QString getToken();

    //setter Methods
    void setToken(QString);

};

#endif // CLIENT_H

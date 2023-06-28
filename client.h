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
    Client(QString, QString);//object for login
  
    QPair<QString, QString> Signup();
    QPair<QString , QString> Login(QString, QString);
    void Logout(QString, QString);

    //getter Merhods
    QString getToken();

    //setter Methods
    void setToken(QString);

};

#endif // CLIENT_H

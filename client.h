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
    QPair<QString , QString> Login();
    QPair<QString , QString> Logout();

    //getter Merhods
    QString getToken();
    QString getUsername();
    QString getPassword();

    //setter Methods
    void setToken(QString);

};

#endif // CLIENT_H

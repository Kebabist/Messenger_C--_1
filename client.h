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
    Client();
    Client(QString, QString , QString , QString);
    Client(QString, QString);//login constructor

    QPair<QString, QString> Signup();
    QPair<QString , QString> Login();
    QPair<QString , QString> Logout();
    void WriteClient();
    void ReadClient();
    void RemoveClientDir();
    Client(QString, QString);//object for login
  


    //getter Merhods
    QString getToken();
    QString getUsername();
    QString getPassword();

    //setter Methods
    void setToken(QString);
};

#endif // CLIENT_H

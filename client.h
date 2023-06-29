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
    void Logout();
    void WriteClient();
    void ReadClient();
    void RemoveClientDir();

    //getter Merhods
    QString getToken();

    //setter Methods
    void setToken(QString);
};

#endif // CLIENT_H

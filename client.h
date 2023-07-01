#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>

class Client
{
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
    void ClientState();
    //getter Merhods
    QString getToken();

    //setter Methods
    void setToken(QString);

private:
    QString username;
    QString password;
    QString firstname;
    QString lastname;
    QString token;
};

#endif // CLIENT_H

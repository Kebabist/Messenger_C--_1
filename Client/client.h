#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QString>

class Client
{
public:
    Client();
    Client(QString, QString , QString , QString);
    Client(QString, QString);//object for login

    QPair<QString, QString> Signup();
    QPair<QString , QString> Login();
    QPair<QString , QString> Logout();
    void WriteClient();
    void ReadClient();
    void RemoveClientDir();
    void ClientState();
    //getter Merhods
    QString getToken();
    QString getUsername();
    QString getPassword();

    //setter Methods
    void setToken(QString);
    void setPassword(QString);
    void setUsername(QString);

private:
    QString username;
    QString password;
    QString firstname;
    QString lastname;
    QString token;
};

#endif // CLIENT_H

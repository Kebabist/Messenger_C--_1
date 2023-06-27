#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QWidget>
#include "user.h"
#include "httphandler.h"
#include "urlmaker.h"

class Client:public user
{
public:
    Client(QString, QString , QString , QString);
  
    void Signup();
    void Login(QString, QString);
    void Logout(QString, QString);

};

#endif // CLIENT_H

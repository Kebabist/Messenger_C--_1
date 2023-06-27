#ifndef USER_H
#define USER_H

#include <QWidget>
#include "urlmaker.h"
#include "httphandler.h"

namespace Ui {
class user;
}

class user : public virtual QWidget
{
    Q_OBJECT

public:
    explicit user(QWidget *parent = nullptr);

    //group related functions
    void joingroup(QString);
    void getgrouplist();
    void getgroupmessages(QString, QString);
    void sendgroupmessage(QString , QString);

    //getter Merhods
    QString getToken();
    QString getusername();
    QString getpassword();
    QString getfirstname();
    QString getlastname();

    //setter Methods
    void setToken(QString);
    void setusername(QString);
    void setpassword(QString);
    void setfirstname(QString);
    void setlastname(QString);
    ~user();

private:
    QString username;
    QString password;
    QString firstname;
    QString lastname;
    QString token;
    Ui::user *ui;
};

#endif // USER_H


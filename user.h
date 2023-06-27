#ifndef USER_H
#define USER_H

#include <QWidget>
#include "urlmaker.h"
#include "httphandler.h"

namespace Ui {
class user;
}

class user : public QWidget
{
    Q_OBJECT

public:
    explicit user(QWidget *parent = nullptr);
    void join(QString);
    void getlist();

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

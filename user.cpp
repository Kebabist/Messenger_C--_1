#include "user.h"
#include "ui_user.h"

user::user(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::user)
{
    ui->setupUi(this);
}

user::~user()
{
    delete ui;
}


//join group note that the function is called on a client object
void user::join(QString desiredgroup){
    HttpHandler http;
    QString token = this->getToken();
    QString arguments = "group_name="+desiredgroup;
    urlmaker newurl("joingroup", token , arguments);
    const QString url = newurl.generate();
    QPair<QJsonObject, bool> response = http.makeRequest(url);
    if(response.second){
        QJsonObject jsonObj = response.first;
        if (jsonObj.contains("code")){
            QString code = jsonObj.value("code").toString();
            if (code == "200"){
                QString message = jsonObj.value("message").toString();
                qDebug() <<message;
            }else if (code == "204") {
                QString message = jsonObj.value("message").toString();
                qDebug() << "join group successfully : " <<message << "Error code : " << code;
            }
        }
    }
}


//get list of joined groupes
void user::getlist(){
    HttpHandler http;
    QString token = this->getToken();
    QString arguments;
    urlmaker newurl("getgrouplist", token , arguments);
    const QString url = newurl.generate();
    QPair<QJsonObject, bool> response = http.makeRequest(url);
    if(response.second){
        QJsonObject jsonObj = response.first;
        if (jsonObj.contains("code")){
            //QString code = jsonObj.value("code").toString();
            for (auto it = jsonObj.begin(); it != jsonObj.end(); ++it) {
                // Check if the current key starts with "block"
                QString key = it.key();
                if (key.startsWith("block")) {
                    QJsonObject blockObject = it.value().toObject();
                    if (blockObject.contains("group_name")) {
                        QString groupName = blockObject.value("group_name").toString();
                        // Process the groupName
                        qDebug() << "Group Name:" << groupName;
                    }
                }
            }
            QString message = jsonObj.value("message").toString();
            qDebug() <<message;
        }
    }
}


//getter Merhods
QString user::getToken(){
    return token;
}
QString user::getfirstname(){
    return firstname;
}
QString user::getlastname(){
    return lastname;
}
QString user::getusername(){
    return username;
}
QString user::getpassword(){
    return password;
}

//setter Methods
void user::setToken(QString token){
    this->token = token;
}
void user::setfirstname(QString firstname){
    this->firstname = firstname;
}
void user::setlastname(QString lastname){
    this->lastname = lastname;
}
void user::setusername(QString username){
    this->username = username;
}
void user::setpassword(QString password){
    this->password = password;
}

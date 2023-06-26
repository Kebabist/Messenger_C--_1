#include "client.h"
#include "httphandler.h"
#include "urlmaker.h"
#include <QDebug>

Client::Client(QString username ,QString password ,QString firstname ,QString lastname)
{
    this->username = username;
    this->password = password;
    this->firstname = firstname;
    this->lastname = lastname;
}


void Client::Signup(){
    HttpHandler http;
    QString arguments;
    arguments = "username="+username+"&"+"password="+password+"&"+"firstname="+firstname+"&"+"lastname="+lastname;
    urlmaker newurl("signup", "token" , arguments);
    const QString url = newurl.generate();
    QPair<QJsonObject, bool> response = http.makeRequest(url);
    if(response.second){
        QJsonObject jsonObj = response.first;
        if (jsonObj.contains("code")){
            QString code = jsonObj.value("code").toString();
            if (code == "200"){
                QString message = jsonObj.value("message").toString();
                qDebug() <<message;
                //redirect to login page implement with gui
            }else if (code == "204") {
                QString message = jsonObj.value("message").toString();
                qDebug() <<message;
                //user already exists implement with gui
            }
        }
    }
}


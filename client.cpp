#include "client.h"
#include <QDebug>

//constructor of client class
Client::Client(QString username ,QString password ,QString firstname ,QString lastname)
{
    setusername(username);
    setpassword(password);
    setfirstname(firstname);
    setlastname(lastname);
}



//lets the user signup in messenger
void Client::Signup(){
    HttpHandler http;
    QString arguments;
    arguments = "username="+getusername()+"&"+"password="+getpassword()+"&"+"firstname="+getfirstname()+"&"+"lastname="+getlastname();
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

//lets the users login using their username and password
void Client::Login(QString username, QString password) {
    //Request Example: http://api.barafardayebehtar.ml:8080/login?username=sara&password=1234
    QString arguments = "username="+getusername()+"&password="+getpassword();
    urlmaker login_url("login" , arguments);
    const QString url = login_url.generate();

    HttpHandler http;
    QPair<QJsonObject, bool> response = http.makeRequest(url);

    if (response.second) {
        QJsonObject jsonObj = response.first;
        if (jsonObj.contains("message") && jsonObj.contains("code")) {
            QString message = jsonObj.value("message").toString();
            QString code = jsonObj.value("code").toString();
            if(message ==  "Logged in Successfully" && code == "200"){
                QString token = jsonObj.value("token").toString();
                setToken(token);
                qDebug()<<"token assigned"<< token;
            }
        }
    } else {
        qDebug() << "Error: Request was not successful";
    }

}

//lets the user logout of messenger client
void Client::Logout(QString, QString){
    QString arguments = "username="+this->getusername()+"&password="+this->getpassword();
        urlmaker login_url("logout" , arguments);
        const QString url = login_url.generate();
        HttpHandler http;
        QPair<QJsonObject, bool> response = http.makeRequest(url);
            if (response.second) {
                QJsonObject jsonObj = response.first;

                QString token = jsonObj.value("token").toString();
                qDebug() << "token:" << token;
                if (jsonObj.contains("message")) {
                    QString message = jsonObj.value("message").toString();
                    qDebug() << "Message:" << message;
                } else {
                    qDebug() << "Message key not found in JSON object";
                }
                if (jsonObj.contains("code")) {
                    QString code = jsonObj.value("code").toString();
                    qDebug() << "Code:" << code;
                } else {
                    qDebug() << "Code key not found in JSON object";
                }
            } else {
                qDebug() << "Error: Request was not successful";
            }
}


#include "client.h"
#include "urlmaker.h"
#include "httphandler.h"

Client::Client(QString username ,QString password ,QString firstname ,QString lastname)
{
    this->username = username;
    this->password = password;
    this->firstname = firstname;
    this->lastname = lastname;
}

//getter Merhods
QString Client::getToken(){
    return token;
}

//setter Methods
void Client::setToken(QString token){
    this->token = token;
}

void Client::Singup(){
    //send a http request to the server with url = http://api.barafardayebehtar.ml:8080/signup?username=user&password=pass&firstname=first&lastname=last
    //handle the servers response
}

//get username and password from input and validates the user by communicating with server
void Client::Login(QString username, QString password) const{
    //Request Example: http://api.barafardayebehtar.ml:8080/login?username=sara&password=1234
    QString arguments = "username="+username+"&password="+password;
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

#include "group.h"
#include "ui_group.h"


group::group(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::group)
{
    ui->setupUi(this);
}

group::group(QString name , QString title){
    group_name = name;
    group_title = title;
}


//create new group
void group::create(Client &c){
    HttpHandler http;
    QString token = c.getToken();
    QString arguments = "group_name="+this->group_name+"&"+"group_title="+group_title;
    urlmaker newurl("creategroup", token , arguments);
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
                qDebug() <<message << "Error code : " << code;
            }
        }
    }
}

//join group
void group::join(Client &c){
    HttpHandler http;
    QString token = c.getToken();
    QString arguments = "group_name="+this->group_name;
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
                qDebug() <<message << "Error code : " << code;
            }
        }
    }
}


group::~group()
{
    delete ui;
}

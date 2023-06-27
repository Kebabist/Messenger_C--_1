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
void group::join(Client &c , QString desiredgroup){
    HttpHandler http;
    QString token = c.getToken();
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
void group::getlist(Client &c){
    HttpHandler http;
    QString token = c.getToken();
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


group::~group()
{
    delete ui;
}

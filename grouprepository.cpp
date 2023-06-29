#include "grouprepository.h"
#include <QDateTime>

//#include "Ui_grouprepository.h"

//GroupRepository::GroupRepository(QWidget *parent) :
//    QWidget(parent),
//    ui(new Ui::GroupRepository)
//{
//    ui->setupUi(this);
//}

//GroupRepository default constructor
GroupRepository::GroupRepository()
{}

//destructor
GroupRepository::~GroupRepository()
{}

//setter function
void GroupRepository::setGroupsList(const Group& newgroup ){
    if (!Groups_list.contains(newgroup)) {
        Groups_list.append(newgroup);
    }
}

//getter function
const QList<Group>& GroupRepository::getGrouplist() const{
    return Groups_list;
}

//create new group
void GroupRepository::createGroup(Client &c, QString gname){
    HttpHandler http;
    QString token = "d7928f6dae40dffdf4be67b24e242ee7";
    QString arguments = "group_name="+gname;//+"&"+"group_title="+g.getGrouptitle();
    urlmaker newurl("creategroup", token , arguments);
    const QString url = newurl.generate();
    QPair<QJsonObject, bool> response = http.makeRequest(url);
    if(response.second){
        QJsonObject jsonObj = response.first;
        QJsonDocument doc(jsonObj);
        QString jsonString = doc.toJson(QJsonDocument::Indented);
        qDebug().noquote() << jsonString;
        if (jsonObj.contains("code")){
            QString code = jsonObj.value("code").toString();
            if (code == "200"){
                QString message = jsonObj.value("message").toString();
                qDebug() <<message;
                GroupRepository gr;
                Group g( "title" , gname); //title is given staticly, change later
                gr.setGroupsList(g);
            }else if (code == "204") {
                QString message = jsonObj.value("message").toString();
                qDebug() <<message << "Error code : " << code;
            }
        }
    }
}


////join group
void GroupRepository::joinGroup(Client &c , QString dstgroup){
    HttpHandler http;
    QString token = "d7928f6dae40dffdf4be67b24e242ee7";
    QString arguments = "group_name="+dstgroup;
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
                GroupRepository gr;
                Group g( "title" , dstgroup); //title is given staticly, change later
                gr.setGroupsList(g);
            }else if (code == "204") {
                QString message = jsonObj.value("message").toString();
                qDebug() << "join group successfully : " <<message << "Error code : " << code;
            }
        }
    }
}



//get list of joined groupes
void GroupRepository::getGrouplist(Client &c){
    HttpHandler http;
    QString token = "d7928f6dae40dffdf4be67b24e242ee7";
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
                        Group g("" , groupName);
                        Groups_list.push_back(g);
                        qDebug() << "Group Name:" << groupName;
                    }
                }
            }
            QString message = jsonObj.value("message").toString();
            qDebug() <<message;
        }
    }
}

//send message in a group chat
void GroupRepository::sendmessageGroup(QString desiredgroup , QString text , Client &c){
    HttpHandler http;
    QString token = "d7928f6dae40dffdf4be67b24e242ee7";
    QString arguments = "dst="+desiredgroup+"&"+"body="+text;
    urlmaker newurl("sendmessagegroup", token , arguments);
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
                qDebug()  <<message << "Error code : " << code;
            }
        }
    }
}


//get group messages
void GroupRepository::getGroupchats(Client &c , QString dst , QString date){
    HttpHandler http;
    QString token = "d7928f6dae40dffdf4be67b24e242ee7";
    QString arguments = "dst="+dst+"&"+"date="+date;
    urlmaker newurl("getgroupchats", token , arguments);
    const QString url = newurl.generate();
    QPair<QJsonObject, bool> response = http.makeRequest(url);
    if(response.second){
        QJsonObject jsonObj = response.first;
        if (jsonObj.contains("code")) {
            QString code = jsonObj.value("code").toString();
            if (code == "200") {
                QString message = jsonObj.value("message").toString();
                qDebug() << message;
                for (auto it = jsonObj.begin(); it != jsonObj.end(); ++it) {
                    QString key = it.key();
                    if (key.startsWith("block")) {
                        QJsonObject blockObject = it.value().toObject();
                        if (blockObject.contains("body") && blockObject.contains("src")) {
                            QString body = blockObject.value("body").toString();
                            QString src = blockObject.value("src").toString();
                            qDebug() << "message: " << body << " sent by : " << src;
                            QString messageDate = blockObject.value("date").toString();
                            QString dateStr = messageDate;
                            QDateTime date = QDateTime::fromString(dateStr, "yyyy-MM-dd hh:mm:ss");
                            QString newDateStr = date.toString("yyyyMMddhhmmss");
                            QString messageSource = blockObject.value("src").toString();
                            QString messageContent = blockObject.value("body").toString();
                            for (auto& group : Groups_list) {
                                if (group.getGroupname() == dst) {
                                    group.setGroupmessages(newDateStr,messageSource,messageContent);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}



void GroupRepository::display() {
    qDebug() << "Display called";
    for ( auto &group : this->Groups_list) {
        if (group.getGroupname() == "nah123123") {
            QMultiMap<QString, QPair<QString, QString>> map = group.getGroupmessages();
            if (map.size() == 0) {
                qDebug() << "No messages in group " << group.getGroupname();
            } else {
                QMultiMapIterator<QString, QPair<QString, QString>> i(map);
                while (i.hasNext()) {
                    i.next();
                    qDebug() << "Key:" << i.key() << "Values:" << i.value().first << i.value().second;
                }
            }
        }
    }
}

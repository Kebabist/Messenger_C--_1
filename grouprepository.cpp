#include "grouprepository.h"
#include "exceptionhandler.h"
#include <QDateTime>
#include <QWidget>
#include <QList>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDir>
#include <QFile>
#include <QByteArray>
#include <QStandardPaths>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include "exceptionhandler.h"
#include"group.h"
#include "httpHandler.h"
#include "urlmaker.h"
#include "client.h"

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
const QList<Group>& GroupRepository::getGroup_list() const{
    return Groups_list;
}

//create new group
void GroupRepository::createGroup(Client &c, QString gname){
    HttpHandler http;
    QString token = "5eab6a7ec57eb020634f5998254aeeaa";
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
    QString token = "5eab6a7ec57eb020634f5998254aeeaa";
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
    QString token = "5eab6a7ec57eb020634f5998254aeeaa";
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
    QString token = "5eab6a7ec57eb020634f5998254aeeaa";
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
    QString token = "5eab6a7ec57eb020634f5998254aeeaa";
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

//Writes Client data to a file
void GroupRepository::WriteGroupsmessages() {
    // Create a file for each group and add their messages to them
    QString filename;
    QString homeDir = QDir::homePath();
    QDir clientDir(homeDir + QDir::separator() + "groups");
    if (!clientDir.exists()) {
        clientDir.mkpath(".");
    }
    qDebug() << "made file";
    for (const auto& g : Groups_list) {
        filename = clientDir.filePath(g.getGroupname() + ".json");
        QFile file(filename);
        if (file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
            QJsonArray messageArray;
            for (QMultiMap<QString, QPair<QString, QString>>::const_iterator it = g.getGroupmessages().constBegin(); it != g.getGroupmessages().constEnd(); ++it) {
                QJsonObject messageObject;
                messageObject["timestamp"] = it.key();
                messageObject["src"] = it.value().first;
                messageObject["message"] = it.value().second;
                messageArray.append(messageObject);
            }
            QJsonDocument messageDoc(messageArray);
            QByteArray messageData = messageDoc.toJson();
            file.write(messageData);
            file.close();
        } else {
            qDebug() << "Failed to open file " << filename << " for writing";
        }
    }
}

//reades Client data from a file
void GroupRepository::ReadGroupsmessages() {
    try {
        // Create a directory for the group files, if it doesn't already exist
        QString homeDir = QDir::homePath();
        QDir groupsDir(homeDir + QDir::separator() + "groups");
        if (!groupsDir.exists()) {
            groupsDir.mkpath(".");
        }

        // Get a list of all the JSON files in the directory
        QStringList filters;
        filters << "*.json";
        QStringList groupFiles = groupsDir.entryList(filters, QDir::Files);

        // Read each group file and create a Group object from its data
        for (const QString& groupFile : groupFiles) {
            QString groupName = groupFile.left(groupFile.lastIndexOf(".json"));
            Group group("", groupName);

            QString filename = groupsDir.filePath(groupFile);
            QFile file(filename);

            if (file.open(QIODevice::ReadOnly)) {
                QJsonDocument groupDoc = QJsonDocument::fromJson(file.readAll());
                QJsonArray messageArray = groupDoc.array();

                for (int i = 0; i < messageArray.size(); ++i) {
                    QJsonObject messageObj = messageArray.at(i).toObject();
                    QString timestamp = messageObj.value("timestamp").toString();
                    QString message = messageObj.value("message").toString();
                    QString src = messageObj.value("src").toString();
                    group.setGroupmessages(src, message, timestamp);
                }

                Groups_list.append(group);
                file.close();
            }
            else {
                // Throw an exception if the file could not be opened for reading
                QString message = "Could not open file " + filename + " for reading";
                QString code = "FILE_OPEN_ERROR";
                throw ExceptionHandler(message, code);
            }
        }
    }
    catch (const ExceptionHandler& e) {
        // Handle any exceptions thrown during file reading
        qDebug() << "Error reading group files: " << e.message() << " (" << e.code() << ")";
    }
}


//removes client directory & its files after logout
void GroupRepository::RemoveGroupsDir(){
    try {
        QString homeDir = QDir::homePath();
        QDir groupsDir(homeDir + QDir::separator() + "groups");

        // Remove all the files in the directory
        QFileInfoList fileList = groupsDir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden | QDir::Files);
        for (const QFileInfo& fileInfo : fileList) {
            if (!fileInfo.dir().remove(fileInfo.fileName())) {
                QString message = "Could not remove file " + fileInfo.absoluteFilePath();
                QString code = "NO_GROUP_FILE";
                throw ExceptionHandler(message, code);
            }
        }

        // Remove the directory itself
        if (!groupsDir.rmdir(".")) {
            QString message = "Could not remove directory " + groupsDir.absolutePath();
            QString code = "NO_GROUP_DIRECTORY";
            throw ExceptionHandler(message, code);
        }
    } catch (const ExceptionHandler& e) {
        // Handle the exception
        qDebug() << "Error: " << e.message() << " (" << e.code() << ")";
        // Re-throw Here if needed
        // throw;
    } catch (...) {
        // Handle any other exceptions
        qDebug() << "Unknown error occurred";
    }
}

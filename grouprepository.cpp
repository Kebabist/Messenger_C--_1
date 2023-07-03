#include <QDateTime>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDir>
#include <QFile>
#include <QByteArray>
#include <QStandardPaths>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include "grouprepository.h"
#include "group.h"
#include "exceptionhandler.h"
#include "httpHandler.h"
#include "urlmaker.h"

//GroupRepository default constructor
GroupRepository::GroupRepository()
{}

//destructor
GroupRepository::~GroupRepository()
{}

//create new group
QString GroupRepository::create(QString token, QString groupName){
    HttpHandler http;
    QString arguments = "group_name="+groupName;
    urlmaker newurl("creategroup", token , arguments);
    const QString url = newurl.generate();
    QPair<QJsonObject, bool> response = http.makeRequest(url);
    QString responseMessage;
    if(response.second){
        QJsonObject jsonObj = response.first;
        QJsonDocument doc(jsonObj);
        QString jsonString = doc.toJson(QJsonDocument::Indented);
        qDebug().noquote() << jsonString;
        if (jsonObj.contains("code")){
            QString code = jsonObj.value("code").toString();
            if (code == "200"){
                responseMessage = jsonObj.value("message").toString();
                qDebug() <<responseMessage;

                // Create the Group object using std::make_unique
                std::unique_ptr<Group> group = std::make_unique<Group>(groupName);

                // Add the Group object to the list using the unique_ptr
                setList(std::move(group));
            }
            else if (code != "200") {  //handled by UI
                responseMessage = jsonObj.value("message").toString();
                qDebug() <<responseMessage << "Error code : " << code;
            }
        }
    }
    return responseMessage;
}

////join group
QString GroupRepository::join(QString token , QString groupName){
    HttpHandler http;
    QString arguments = "group_name="+groupName;
    urlmaker newurl("joingroup", token , arguments);
    const QString url = newurl.generate();
    QPair<QJsonObject, bool> response = http.makeRequest(url);
    QString responseMessage;
    if(response.second){
        QJsonObject jsonObj = response.first;
        if (jsonObj.contains("code")){
            QString code = jsonObj.value("code").toString();
            if (code == "200"){
                responseMessage = jsonObj.value("message").toString();
                qDebug() <<responseMessage;

                // Create the Group object using std::make_unique
                std::unique_ptr<Group> group = std::make_unique<Group>(groupName);

                // Add the Group object to the list using the unique_ptr
                setList(std::move(group));
            }
            else if (code != "200") { //handled by UI
                responseMessage = jsonObj.value("message").toString();
                qDebug() <<responseMessage << "Error code : " << code;
            }
        }
    }
    return responseMessage;
}

//get list of joined groupes
void GroupRepository::getList(QString token){
    HttpHandler http;
    QString arguments="";
    urlmaker newurl("getgrouplist", token , arguments);
    const QString url = newurl.generate();
    QPair<QJsonObject, bool> response = http.makeRequest(url);
    if(response.second){
        QJsonObject jsonObj = response.first;
        if (jsonObj.contains("code")){
            for (auto it = jsonObj.begin(); it != jsonObj.end(); ++it) {
                // Check if the current key starts with "block"
                QString key = it.key();
                if (key.startsWith("block")) {
                    QJsonObject blockObject = it.value().toObject();
                    if (blockObject.contains("group_name")) {
                        QString groupName = blockObject.value("group_name").toString();

                        // Create the Group object using std::make_unique
                        std::unique_ptr<Group> group = std::make_unique<Group>(groupName);

                        // Add the Group object to the list using the unique_ptr
                        setList(std::move(group));
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
QString GroupRepository::sendMessage(QString token, QString groupName , QString message){
    HttpHandler http;
    QString arguments = "dst="+groupName+"&"+"body="+message;
    urlmaker newurl("sendmessagegroup", token , arguments);
    const QString url = newurl.generate();
    QPair<QJsonObject, bool> response = http.makeRequest(url);
    QString responseMessage;
    if(response.second){
        QJsonObject jsonObj = response.first;
        if (jsonObj.contains("code")){
            QString code = jsonObj.value("code").toString();
            if (code == "200"){ //handled by UI (every time we send a message we call getgroupmessage method and get the rest of the messages from the saerver
                responseMessage = jsonObj.value("message").toString();
                qDebug() <<responseMessage;
            }else if (code != "200") { //handled by UI
                responseMessage = jsonObj.value("message").toString();
                qDebug()  <<responseMessage << "Error code : " << code;
            }
        }
    }
    return responseMessage;
}

//function that checks the state of Messages multimap and returns the latest time stamp available in it
const QString GroupRepository::findLatestDate(QString groupName){
    readMessages();
    for (auto& groupPtr : list) {
        if (groupPtr->getName() == groupName) {
            QMultiMap<QString, QPair<QString, QString>> temp = groupPtr->getMessages();
            if (!temp.empty()) {
                const QString lastdate = temp.lastKey();
                return lastdate;
            }
        }
    }
    return "";
}

//get group messages
void GroupRepository::getChats(QString token, QString groupName , QString date){
    HttpHandler http;
    QString arguments;
    if (date !=""){
        arguments = "dst="+groupName+"&"+"date="+date;
    }
    else{
        QString lastdate = findLatestDate(groupName);
        if(lastdate != ""){
           arguments = "dst="+groupName+"&"+"date="+lastdate;
        }
        else arguments = "dst="+groupName;
    }
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
                            QString Date = blockObject.value("date").toString();
                            QDateTime date = QDateTime::fromString(Date, "yyyy-MM-dd hh:mm:ss");
                            QString strDate = date.toString("yyyyMMddhhmmss");
                            for (auto& groupPtr : list) {
                                if (groupPtr->getName() == groupName) {
                                    groupPtr->setMessage(src, body, strDate);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

//Writes Group data to a file
void GroupRepository::writeMessages() {
    try{
        // Create a file for each group and add their messages to them
        QString filename;
        QString homeDir = QDir::homePath();
        QDir groupsDir(homeDir + QDir::separator() + "Groups");
        if (!groupsDir.exists()) {
            groupsDir.mkpath(".");
        }
        for (auto& groupPtr : list){
            filename = groupsDir.filePath(groupPtr->getName() + ".json");
            QFile file(filename);
            if (file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
                QJsonArray messageArray;
                for (QMultiMap<QString, QPair<QString, QString>>::const_iterator it = groupPtr->getMessages().constBegin(); it != groupPtr->getMessages().constEnd(); ++it) {
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
                // Throw an exception if the file could not be opened for writing
                QString message = "Could not open file " + filename + " for writing";
                QString code = "FILE_OPEN_ERROR";
                throw ExceptionHandler(message, code);
            }
        }
    }
    catch (const ExceptionHandler& e) {
        // Handle the exception
        qDebug() << "Error: " << e.message() << " (" << e.code() << ")";
        //re-throw here if it's needed to handle the exception further up the call stack
        // throw;
    }
    catch (...) {
        // Handle any other exceptions
        qDebug() << "Unknown error occurred";
    }
}

//reades Group data from a file
void GroupRepository::readMessages() {
    try {
        // Create a directory for the group files, if it doesn't already exist
        QString homeDir = QDir::homePath();
        QDir groupsDir(homeDir + QDir::separator() + "Groups");
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
            // Create the Group object using std::make_unique
            std::unique_ptr<Group> group = std::make_unique<Group>(groupName);

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
                    group->setMessage(src, message, timestamp);
                }

                // Add the Group object to the list using the unique_ptr
                setList(std::move(group));
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
        // Handle the exception
        qDebug() << "Error: " << e.message() << " (" << e.code() << ")";
        //re-throw here if it's needed to handle the exception further up the call stack
        // throw;
    }
    catch (...) {
        // Handle any other exceptions
        qDebug() << "Unknown error occurred";
    }
}


//removes Group directory & its files after logout
void GroupRepository::removeDir(){
    try {
        QString homeDir = QDir::homePath();
        QDir groupsDir(homeDir + QDir::separator() + "Groups");

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

//Test Display function
void GroupRepository::display() {
    qDebug() << "Display called";
    for (auto& groupPtr : list) {
        if (groupPtr->getName() == "nah123123") {
            QMultiMap<QString, QPair<QString, QString>> map = groupPtr->getMessages();
            if (map.size() == 0) {
                qDebug() << "No messages in group " << groupPtr->getName();
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

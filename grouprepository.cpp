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

//GroupRepository default constructor
GroupRepository::GroupRepository()
{}

//destructor
GroupRepository::~GroupRepository()
{}

//setter function
void GroupRepository::setGroupsList(std::unique_ptr<Group> newgroup) {
    bool found = false;
    for (const auto& groupPtr : Groups_list) {
        if (groupPtr->getGroupname() == newgroup->getGroupname()) {
            found = true;
            break;
        }
    }
    if (!found) {
        Groups_list.emplace_back(std::move(newgroup));
    }
}
//void GroupRepository::setGroupsList(std::unique_ptr<Group> newgroup) {
//    QList<std::unique_ptr<Group>> tempGroupsList = Groups_list;
//    try {
//         if (!Groups_list.contains(*newgroup)) {
//             Groups_list.append(std::move(newgroup));
//         }
//    }
//    catch (...) {
//         // Reset the state of Groups_list to its previous value
//         Groups_list = std::move(tempGroupsList);
//    }
//}

//getter function
const std::vector<std::unique_ptr<Group>>& GroupRepository::getGroup_list() const {
    return Groups_list;
}

//create new group
void GroupRepository::createGroup(QString token, QString groupName){
    HttpHandler http;
    QString arguments = "group_name="+groupName;
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

                // Create the Group object using std::make_unique
                std::unique_ptr<Group> group = std::make_unique<Group>(groupName);

                // Add the Group object to the list using the unique_ptr
                setGroupsList(std::move(group));
            }
            else if (code != "200") {  //handled by UI
                QString message = jsonObj.value("message").toString();
                qDebug() <<message << "Error code : " << code;
            }
        }
    }
}

////join group
void GroupRepository::joinGroup(QString token , QString groupName){
    HttpHandler http;
    QString arguments = "group_name="+groupName;
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

                // Create the Group object using std::make_unique
                std::unique_ptr<Group> group = std::make_unique<Group>(groupName);

                // Add the Group object to the list using the unique_ptr
                setGroupsList(std::move(group));
            }
            else if (code != "200") { //handled by UI
                QString message = jsonObj.value("message").toString();
                qDebug() <<message << "Error code : " << code;
            }
        }
    }
}

//get list of joined groupes
void GroupRepository::getGrouplist(QString token){
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
                        setGroupsList(std::move(group));
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
void GroupRepository::sendmessageGroup(QString token, QString groupName , QString message){
    HttpHandler http;
    QString arguments = "dst="+groupName+"&"+"body="+message;
    urlmaker newurl("sendmessagegroup", token , arguments);
    const QString url = newurl.generate();
    QPair<QJsonObject, bool> response = http.makeRequest(url);
    if(response.second){
        QJsonObject jsonObj = response.first;
        if (jsonObj.contains("code")){
            QString code = jsonObj.value("code").toString();
            if (code == "200"){ //handled by UI (every time we send a message we call getgroupmessage method and get the rest of the messages from the saerver
                QString message = jsonObj.value("message").toString();
                qDebug() <<message;
            }else if (code != "200") { //handled by UI
                QString message = jsonObj.value("message").toString();
                qDebug()  <<message << "Error code : " << code;
            }
        }
    }
}

//function that checks the state of Messages multimap and returns the latest time stamp available in it
const QString GroupRepository::findLatestdate(QString groupName) const {
    for (auto& groupPtr : Groups_list) {
        if (groupPtr->getGroupname() == groupName) {
            QMultiMap<QString, QPair<QString, QString>> temp = groupPtr->getGroupmessages();
            if (!temp.empty()) {
                const QString lastdate = temp.lastKey();
                return lastdate;
            }
        }
    }
    return "";
}


//get group messages
void GroupRepository::getGroupchats(QString token, QString groupName , QString date){
    HttpHandler http;
    QString arguments;
    QPair<Group*, QString> flag(nullptr, "");
    if (date !=""){
        arguments = "dst="+groupName+"&"+"date="+date;
    }
    else{
       QString lastdate = findLatestdate(groupName);
        if(flag.second != ""){
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
                            for (auto& groupPtr : Groups_list) {
                                if (groupPtr->getGroupname() == groupName) {
                                    groupPtr->setGroupmessages(src, body, strDate);
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
void GroupRepository::WriteGroupsmessages() {
    // Create a file for each group and add their messages to them
    QString filename;
    QString homeDir = QDir::homePath();
    QDir clientDir(homeDir + QDir::separator() + "groups");
    if (!clientDir.exists()) {
        clientDir.mkpath(".");
    }
    qDebug() << "made file";
    for (auto& groupPtr : Groups_list){
        filename = clientDir.filePath(groupPtr->getGroupname() + ".json");
        QFile file(filename);
        if (file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
            QJsonArray messageArray;
            for (QMultiMap<QString, QPair<QString, QString>>::const_iterator it = groupPtr->getGroupmessages().constBegin(); it != groupPtr->getGroupmessages().constEnd(); ++it) {
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

//reades Group data from a file
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
                    group->setGroupmessages(src, message, timestamp);
                }

                // Add the Group object to the list using the unique_ptr
                setGroupsList(std::move(group));
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


//removes Group directory & its files after logout
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

//Test Display function
void GroupRepository::display() {
    qDebug() << "Display called";
    for (auto& groupPtr : Groups_list) {
        if (groupPtr->getGroupname() == "nah123123") {
            QMultiMap<QString, QPair<QString, QString>> map = groupPtr->getGroupmessages();
            if (map.size() == 0) {
                qDebug() << "No messages in group " << groupPtr->getGroupname();
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

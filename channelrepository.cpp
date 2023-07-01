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
#include "channelrepository.h"
#include "channel.h"
#include "exceptionhandler.h"
#include "httpHandler.h"
#include "urlmaker.h"

//ChannelRepository default constructor
ChannelRepository::ChannelRepository()
{}

//copy constructor
//ChannelRepository::ChannelRepository(const ChannelRepository& other)
//    : list(other.list)
//{}

//destructor
ChannelRepository::~ChannelRepository()
{}

//create new Channel
void ChannelRepository::create(QString token, QString channelName){
    HttpHandler http;
    QString arguments = "channel_name="+channelName;
    urlmaker newurl("createchannel", token , arguments);
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

                // Create the Channel object using std::make_unique
                std::unique_ptr<Channel> channel = std::make_unique<Channel>(channelName);

                // Add the Channel object to the list using the unique_ptr
                setList(std::move(channel));
            }
            else if (code != "200") {  //handled by UI
                QString message = jsonObj.value("message").toString();
                qDebug() <<message << "Error code : " << code;
            }
        }
    }
}

////join Channel
void ChannelRepository::join(QString token , QString channelName){
    HttpHandler http;
    QString arguments = "channel_name="+channelName;
    urlmaker newurl("joinchannel", token , arguments);
    const QString url = newurl.generate();
    QPair<QJsonObject, bool> response = http.makeRequest(url);
    if(response.second){
        QJsonObject jsonObj = response.first;
        if (jsonObj.contains("code")){
            QString code = jsonObj.value("code").toString();
            if (code == "200"){
                QString message = jsonObj.value("message").toString();
                qDebug() <<message;

                // Create the Channel object using std::make_unique
                std::unique_ptr<Channel> channel = std::make_unique<Channel>(channelName);

                // Add the Channel object to the list using the unique_ptr
                setList(std::move(channel));
            }
            else if (code != "200") { //handled by UI
                QString message = jsonObj.value("message").toString();
                qDebug() <<message << "Error code : " << code;
            }
        }
    }
}

//get list of joined Channels
void ChannelRepository::getList(QString token){
    HttpHandler http;
    QString arguments="";
    urlmaker newurl("getchannellist", token , arguments);
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
                    if (blockObject.contains("channel_name")) {
                        QString channelName = blockObject.value("channel_name").toString();

                        // Create the Channel object using std::make_unique
                        std::unique_ptr<Channel> channel = std::make_unique<Channel>(channelName);

                        // Add the Channel object to the list using the unique_ptr
                        setList(std::move(channel));
                        qDebug() << "Channel Name:" << channelName;
                    }
                }
            }
            QString message = jsonObj.value("message").toString();
            qDebug() <<message;
        }
    }
}

//send message in a Channel chat
void ChannelRepository::sendMessage(QString token, QString channelName , QString message){
    HttpHandler http;
    QString arguments = "dst="+channelName+"&"+"body="+message;
    urlmaker newurl("sendmessagechannel", token , arguments);
    const QString url = newurl.generate();
    QPair<QJsonObject, bool> response = http.makeRequest(url);
    if(response.second){
        QJsonObject jsonObj = response.first;
        if (jsonObj.contains("code")){
            QString code = jsonObj.value("code").toString();
            if (code == "200"){ //handled by UI (every time we send a message we call getmessage method and get the rest of the messages from the saerver
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
const QString ChannelRepository::findLatestDate(QString channelName) {
    readMessages();
    for (auto& channelPtr : list) {
        if (channelPtr->getName() == channelName) {
            QMultiMap<QString, QPair<QString, QString>> temp = channelPtr->getMessages();
            if (!temp.empty()) {
                const QString lastdate = temp.lastKey();
                return lastdate;
            }
        }
    }
    return "";
}

//get Channel messages
void ChannelRepository::getChats(QString token, QString channelName , QString date){
    HttpHandler http;
    QString arguments;
    if (date !=""){
        arguments = "dst="+channelName+"&"+"date="+date;
    }
    else{
        QString lastdate = findLatestDate(channelName);
        if(lastdate != ""){
            arguments = "dst="+channelName+"&"+"date="+lastdate;
        }
        else arguments = "dst="+channelName;
    }
    urlmaker newurl("getchannelchats", token , arguments);
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
                            for (auto& channelPtr : list) {
                                if (channelPtr->getName() == channelName) {
                                    channelPtr->setMessage(src, body, strDate);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

//Writes Channel data to a file
void ChannelRepository::writeMessages() {
    // Create a file for each Channel and add their messages to them
    QString filename;
    QString homeDir = QDir::homePath();
    QDir clientDir(homeDir + QDir::separator() + "Channels");
    if (!clientDir.exists()) {
        clientDir.mkpath(".");
    }
    qDebug() << "made file";
    for (auto& channelPtr : list){
        filename = clientDir.filePath(channelPtr->getName() + ".json");
        QFile file(filename);
        if (file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
            QJsonArray messageArray;
            for (QMultiMap<QString, QPair<QString, QString>>::const_iterator it = channelPtr->getMessages().constBegin(); it != channelPtr->getMessages().constEnd(); ++it) {
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

//reades Channel data from a file
void ChannelRepository::readMessages() {
    try {
        // Create a directory for the Channel files, if it doesn't already exist
        QString homeDir = QDir::homePath();
        QDir channelsDir(homeDir + QDir::separator() + "Channels");
        if (!channelsDir.exists()) {
            channelsDir.mkpath(".");
        }

        // Get a list of all the JSON files in the directory
        QStringList filters;
        filters << "*.json";
        QStringList channelFiles = channelsDir.entryList(filters, QDir::Files);

        // Read each Channel file and create a Channel object from its data
        for (const QString& channelFile : channelFiles) {
            QString channelName = channelFile.left(channelFile.lastIndexOf(".json"));
            // Create the Channel object using std::make_unique
            std::unique_ptr<Channel> channel = std::make_unique<Channel>(channelName);

            QString filename = channelsDir.filePath(channelFile);
            QFile file(filename);

            if (file.open(QIODevice::ReadOnly)) {
                QJsonDocument channelDoc = QJsonDocument::fromJson(file.readAll());
                QJsonArray messageArray = channelDoc.array();

                for (int i = 0; i < messageArray.size(); ++i) {
                    QJsonObject messageObj = messageArray.at(i).toObject();
                    QString timestamp = messageObj.value("timestamp").toString();
                    QString message = messageObj.value("message").toString();
                    QString src = messageObj.value("src").toString();
                    channel->setMessage(src, message, timestamp);
                }

                // Add the Channel object to the list using the unique_ptr
                setList(std::move(channel));
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
        qDebug() << "Error reading Channel files: " << e.message() << " (" << e.code() << ")";
    }
}


//removes Channel directory & its files after logout
void ChannelRepository::removeDir(){
    try {
        QString homeDir = QDir::homePath();
        QDir channelsDir(homeDir + QDir::separator() + "Channels");

        // Remove all the files in the directory
        QFileInfoList fileList = channelsDir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden | QDir::Files);
        for (const QFileInfo& fileInfo : fileList) {
            if (!fileInfo.dir().remove(fileInfo.fileName())) {
                QString message = "Could not remove file " + fileInfo.absoluteFilePath();
                QString code = "NO_Channel_FILE";
                throw ExceptionHandler(message, code);
            }
        }

        // Remove the directory itself
        if (!channelsDir.rmdir(".")) {
            QString message = "Could not remove directory " + channelsDir.absolutePath();
            QString code = "NO_Channel_DIRECTORY";
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
void ChannelRepository::display() {
    qDebug() << "Display called";
    for (auto& channelPtr : list) {
        if (channelPtr->getName() == "nah123123") {
            QMultiMap<QString, QPair<QString, QString>> map = channelPtr->getMessages();
            if (map.size() == 0) {
                qDebug() << "No messages in Channel " << channelPtr->getName();
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

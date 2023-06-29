#include "channelrepository.h"
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
#include "channel.h"
#include "httpHandler.h"
#include "urlmaker.h"
#include "client.h"

//ChannelRepository default constructor
ChannelRepository::ChannelRepository()
{}

//destructor
ChannelRepository::~ChannelRepository()
{}

//setter function
void ChannelRepository::setChannelsList(const Channel& newChannel ){
    if (!Channels_list.contains(newChannel)) {
        Channels_list.append(newChannel);
    }
}

//getter function
const QList<Channel>& ChannelRepository::getChannellist() const{
    return Channels_list;
}

//create new Channel
void ChannelRepository::createChannel(Client &c, QString gname){
    HttpHandler http;
    QString token = "d7928f6dae40dffdf4be67b24e242ee7";
    QString arguments = "Channel_name="+gname;//+"&"+"Channel_title="+g.getChanneltitle();
    urlmaker newurl("createChannel", token , arguments);
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
                ChannelRepository gr;
                Channel g(gname); //title is given staticly, change later
                gr.setChannelsList(g);
            }else if (code == "204") {
                QString message = jsonObj.value("message").toString();
                qDebug() <<message << "Error code : " << code;
            }
        }
    }
}


////join Channel
void ChannelRepository::joinChannel(Client &c , QString dstChannel){
    HttpHandler http;
    QString token = "d7928f6dae40dffdf4be67b24e242ee7";
    QString arguments = "Channel_name="+dstChannel;
    urlmaker newurl("joinChannel", token , arguments);
    const QString url = newurl.generate();
    QPair<QJsonObject, bool> response = http.makeRequest(url);
    if(response.second){
        QJsonObject jsonObj = response.first;
        if (jsonObj.contains("code")){
            QString code = jsonObj.value("code").toString();
            if (code == "200"){
                QString message = jsonObj.value("message").toString();
                qDebug() <<message;
                ChannelRepository gr;
                Channel g(dstChannel); //title is given staticly, change later
                gr.setChannelsList(g);
            }else if (code == "204") {
                QString message = jsonObj.value("message").toString();
                qDebug() << "join Channel successfully : " <<message << "Error code : " << code;
            }
        }
    }
}



//get list of joined Channeles
void ChannelRepository::getChannellist(Client &c){
    HttpHandler http;
    QString token = "d7928f6dae40dffdf4be67b24e242ee7";
    QString arguments;
    urlmaker newurl("getChannellist", token , arguments);
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
                    if (blockObject.contains("Channel_name")) {
                        QString ChannelName = blockObject.value("Channel_name").toString();
                        // Process the ChannelName
                        Channel g(ChannelName);
                        Channels_list.push_back(g);
                        qDebug() << "Channel Name:" << ChannelName;
                    }
                }
            }
            QString message = jsonObj.value("message").toString();
            qDebug() <<message;
        }
    }
}

//send message in a Channel chat
void ChannelRepository::sendmessageChannel(QString desiredChannel , QString text , Client &c){
    HttpHandler http;
    QString token = "d7928f6dae40dffdf4be67b24e242ee7";
    QString arguments = "dst="+desiredChannel+"&"+"body="+text;
    urlmaker newurl("sendmessageChannel", token , arguments);
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


//get Channel messages
void ChannelRepository::getChannelchats(Client &c , QString dst , QString date){
    HttpHandler http;
    QString token = "d7928f6dae40dffdf4be67b24e242ee7";
    QString arguments = "dst="+dst+"&"+"date="+date;
    urlmaker newurl("getChannelchats", token , arguments);
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
                            for (auto& Channel : Channels_list) {
                                if (Channel.getChannelname() == dst) {
                                    Channel.setChannelmessages(newDateStr,messageSource,messageContent);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}



void ChannelRepository::display() {
    qDebug() << "Display called";
    for ( auto &Channel : this->Channels_list) {
        if (Channel.getChannelname() == "nah123123") {
            QMultiMap<QString, QPair<QString, QString>> map = Channel.getChannelmessages();
            if (map.size() == 0) {
                qDebug() << "No messages in Channel " << Channel.getChannelname();
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
void ChannelRepository::WriteChannelsmessages() {
    // Create a file for each Channel and add their messages to them
    QString filename;
    QString homeDir = QDir::homePath();
    QDir clientDir(homeDir + QDir::separator() + "Channels");
    if (!clientDir.exists()) {
        clientDir.mkpath(".");
    }
    qDebug() << "made file";
    for (const auto& g : Channels_list) {
        filename = clientDir.filePath(g.getChannelname() + ".json");
        QFile file(filename);
        if (file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
            QJsonArray messageArray;
            for (QMultiMap<QString, QPair<QString, QString>>::const_iterator it = g.getChannelmessages().constBegin(); it != g.getChannelmessages().constEnd(); ++it) {
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
void ChannelRepository::ReadChannelsmessages() {
    try {
        // Create a directory for the Channel files, if it doesn't already exist
        QString homeDir = QDir::homePath();
        QDir ChannelsDir(homeDir + QDir::separator() + "Channels");
        if (!ChannelsDir.exists()) {
            ChannelsDir.mkpath(".");
        }

        // Get a list of all the JSON files in the directory
        QStringList filters;
        filters << "*.json";
        QStringList ChannelFiles = ChannelsDir.entryList(filters, QDir::Files);

        // Read each Channel file and create a Channel object from its data
        for (const QString& ChannelFile : ChannelFiles) {
            QString ChannelName = ChannelFile.left(ChannelFile.lastIndexOf(".json"));
            Channel Channel(ChannelName);

            QString filename = ChannelsDir.filePath(ChannelFile);
            QFile file(filename);

            if (file.open(QIODevice::ReadOnly)) {
                QJsonDocument ChannelDoc = QJsonDocument::fromJson(file.readAll());
                QJsonArray messageArray = ChannelDoc.array();

                for (int i = 0; i < messageArray.size(); ++i) {
                    QJsonObject messageObj = messageArray.at(i).toObject();
                    QString timestamp = messageObj.value("timestamp").toString();
                    QString message = messageObj.value("message").toString();
                    QString src = messageObj.value("src").toString();
                    Channel.setChannelmessages(src, message, timestamp);
                }

                Channels_list.append(Channel);
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


//removes client directory & its files after logout
void ChannelRepository::RemoveChannelsDir(){
    try {
        QString homeDir = QDir::homePath();
        QDir ChannelsDir(homeDir + QDir::separator() + "Channels");

        // Remove all the files in the directory
        QFileInfoList fileList = ChannelsDir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden | QDir::Files);
        for (const QFileInfo& fileInfo : fileList) {
            if (!fileInfo.dir().remove(fileInfo.fileName())) {
                QString message = "Could not remove file " + fileInfo.absoluteFilePath();
                QString code = "NO_Channel_FILE";
                throw ExceptionHandler(message, code);
            }
        }

        // Remove the directory itself
        if (!ChannelsDir.rmdir(".")) {
            QString message = "Could not remove directory " + ChannelsDir.absolutePath();
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

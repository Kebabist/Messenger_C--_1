#include "pvrepository.h"
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
#include "pv.h"
#include "httpHandler.h"
#include "urlmaker.h"
#include "client.h"

//PvRepository default constructor
PvRepository::PvRepository()
{}

//destructor
PvRepository::~PvRepository()
{}

//setter function
void PvRepository::setPvsList(std::unique_ptr<Pv> newpv) {
    bool found = false;
    for (const auto& PvPtr : Pvs_list) {
        if (PvPtr->getPvname() == newpv->getPvname()) {
            found = true;
            break;
        }
    }
    if (!found) {
        Pvs_list.emplace_back(std::move(newpv));
    }
}

//getter function
const std::vector<std::unique_ptr<Pv>>& PvRepository::getPv_list() const {
    return Pvs_list;
}


//get list of joined Pvs
void PvRepository::getPvlist(QString token){
    HttpHandler http;
    QString arguments="";
    urlmaker newurl("getuserlist", token , arguments);
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
                    if (blockObject.contains("src")) {
                        QString pvName = blockObject.value("src").toString();

                        // Create the Pv object using std::make_unique
                        std::unique_ptr<Pv> pv = std::make_unique<Pv>(pvName);

                        // Add the Pv object to the list using the unique_ptr
                        setPvsList(std::move(pv));
                        qDebug() << "Pv Name:" << pvName;
                    }
                }
            }
            QString message = jsonObj.value("message").toString();
            qDebug() <<message;
        }
    }
}

//send message in a Pv chat
void PvRepository::sendmessagePv(QString token, QString pvName , QString message){
    HttpHandler http;
    QString arguments = "dst="+pvName+"&"+"body="+message;
    urlmaker newurl("sendmessageuser", token , arguments);
    const QString url = newurl.generate();
    QPair<QJsonObject, bool> response = http.makeRequest(url);
    if(response.second){
        QJsonObject jsonObj = response.first;
        if (jsonObj.contains("code")){
            QString code = jsonObj.value("code").toString();
            if (code == "200"){ //handled by UI (every time we send a message we call getpvmessage method and get the rest of the messages from the saerver
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
const QString PvRepository::findLatestdate(QString pvName) const {
    for (auto& pvPtr : Pvs_list) {
        if (pvPtr->getPvname() == pvName) {
            QMultiMap<QString, QPair<QString, QString>> temp = pvPtr->getPvmessages();
            if (!temp.empty()) {
                const QString lastdate = temp.lastKey();
                return lastdate;
            }
        }
    }
    return "";
}


//get Pv messages
void PvRepository::getPvchats(QString token, QString pvName , QString date){
    HttpHandler http;
    QString arguments;
    QPair<Pv*, QString> flag(nullptr, "");
    if (date !=""){
        arguments = "dst="+pvName+"&"+"date="+date;
    }
    else{
        QString lastdate = findLatestdate(pvName);
        if(flag.second != ""){
            arguments = "dst="+pvName+"&"+"date="+lastdate;
        }
        else arguments = "dst="+pvName;
    }
    urlmaker newurl("getuserchats", token , arguments);
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
                            for (auto& pvPtr : Pvs_list) {
                                if (pvPtr->getPvname() == pvName) {
                                    pvPtr->setPvmessages(src, body, strDate);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

//Writes Pv data to a file
void PvRepository::WritePvsmessages() {
    // Create a file for each Pv and add their messages to them
    QString filename;
    QString homeDir = QDir::homePath();
    QDir clientDir(homeDir + QDir::separator() + "pvs");
    if (!clientDir.exists()) {
        clientDir.mkpath(".");
    }
    for (auto& pvPtr : Pvs_list){
        filename = clientDir.filePath(pvPtr->getPvname() + ".json");
        QFile file(filename);
        qDebug() << "madefile with name :" << filename;
        if (file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
            QJsonArray messageArray;
            for (QMultiMap<QString, QPair<QString, QString>>::const_iterator it = pvPtr->getPvmessages().constBegin(); it != pvPtr->getPvmessages().constEnd(); ++it) {
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

//reades Pv data from a file
void PvRepository::ReadPvsmessages() {
    try {
        // Create a directory for the Pv files, if it doesn't already exist
        QString homeDir = QDir::homePath();
        QDir pvsDir(homeDir + QDir::separator() + "pvs");
        if (!pvsDir.exists()) {
            pvsDir.mkpath(".");
        }

        // Get a list of all the JSON files in the directory
        QStringList filters;
        filters << "*.json";
        QStringList pvFiles = pvsDir.entryList(filters, QDir::Files);

        // Read each pv file and create a Pv object from its data
        for (const QString& pvFile : pvFiles) {
            QString pvName = pvFile.left(pvFile.lastIndexOf(".json"));
            // Create the Pv object using std::make_unique
            std::unique_ptr<Pv> pv = std::make_unique<Pv>(pvName);

            QString filename = pvsDir.filePath(pvFile);
            QFile file(filename);

            if (file.open(QIODevice::ReadOnly)) {
                QJsonDocument pvDoc = QJsonDocument::fromJson(file.readAll());
                QJsonArray messageArray = pvDoc.array();

                for (int i = 0; i < messageArray.size(); ++i) {
                    QJsonObject messageObj = messageArray.at(i).toObject();
                    QString timestamp = messageObj.value("timestamp").toString();
                    QString message = messageObj.value("message").toString();
                    QString src = messageObj.value("src").toString();
                    pv->setPvmessages(src, message, timestamp);
                }

                // Add the Pv object to the list using the unique_ptr
                setPvsList(std::move(pv));
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
        qDebug() << "Error reading pv files: " << e.message() << " (" << e.code() << ")";
    }
}


//removes Pv directory & its files after logout
void PvRepository::RemovePvsDir(){
    try {
        QString homeDir = QDir::homePath();
        QDir pvsDir(homeDir + QDir::separator() + "pvs");

        // Remove all the files in the directory
        QFileInfoList fileList = pvsDir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden | QDir::Files);
        for (const QFileInfo& fileInfo : fileList) {
            if (!fileInfo.dir().remove(fileInfo.fileName())) {
                QString message = "Could not remove file " + fileInfo.absoluteFilePath();
                QString code = "NO_PV_FILE";
                throw ExceptionHandler(message, code);
            }
        }

        // Remove the directory itself
        if (!pvsDir.rmdir(".")) {
            QString message = "Could not remove directory " + pvsDir.absolutePath();
            QString code = "NO_PV_DIRECTORY";
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
void PvRepository::display() {
    qDebug() << "Display called";
    for (auto& pvPtr : Pvs_list) {
        if (pvPtr->getPvname() == "nah123123") {
            QMultiMap<QString, QPair<QString, QString>> map = pvPtr->getPvmessages();
            if (map.size() == 0) {
                qDebug() << "No messages in pv " << pvPtr->getPvname();
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

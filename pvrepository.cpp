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
void PvRepository::setPvList(const Pv& newPv ){
    if (!Pvs_list.contains(newPv)) {
        Pvs_list.append(newPv);
    }
}

//getter function
const QList<Pv>& PvRepository::getPv_list() const{
    return Pvs_list;
}

//get list of joined Pvs
void PvRepository::getPvlist(Client &c){
    HttpHandler http;
    QString token = "3077fa34139c9cd1ef0edf8fe25b02d4";
    QString arguments;
    urlmaker newurl("getuserlist", token , arguments);
    const QString url = newurl.generate();
    QPair<QJsonObject, bool> response = http.makeRequest(url);
    if(response.second){
        QJsonObject jsonObj = response.first;
        if (jsonObj.contains("code")){
            //QString code = jsonObj.value("code").toString();
            for (auto it = jsonObj.begin(); it != jsonObj.end(); ++it) {
                // Check if the current key starts with "block"
                QString key = it.key();
                qDebug() << jsonObj;
                if (key.startsWith("block")) {
                    QJsonObject blockObject = it.value().toObject();
                    if (blockObject.contains("src")) {
                        QString PvName = blockObject.value("src").toString();  //check the api response
                        // Process the PvName
                        Pv p(PvName);
                        Pvs_list.push_back(p);
                        qDebug() << "Pv Name:" << PvName;
                    }
                }
            }
            QString message = jsonObj.value("message").toString();
            qDebug() <<message;
        }
    }
}

//send message in a Pv chat
void PvRepository::sendmessagePv(QString desiredPv , QString text , Client &c){
    HttpHandler http;
    QString token = "3077fa34139c9cd1ef0edf8fe25b02d4";
    QString arguments = "dst="+desiredPv+"&"+"body="+text;
    urlmaker newurl("sendmessageuser", token , arguments);
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


//get Pv messages
void PvRepository::getPvchats(Client &c , QString dst , QString date){
    HttpHandler http;
    QString token = "3077fa34139c9cd1ef0edf8fe25b02d4";
    QString arguments = "dst="+dst;//+"&"+"date="+date;
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
                            QString messageDate = blockObject.value("date").toString();
                            QString dateStr = messageDate;
                            QDateTime date = QDateTime::fromString(dateStr, "yyyy-MM-dd hh:mm:ss");
                            QString newDateStr = date.toString("yyyyMMddhhmmss");
                            QString messageSource = blockObject.value("src").toString();
                            QString messageContent = blockObject.value("body").toString();
                            for (auto& pv : Pvs_list) {
                                if (pv.getPvname() == dst) {
                                    pv.setPvmessages(newDateStr,messageSource,messageContent);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}



void PvRepository::display() {
    qDebug() << "Display called";
    for ( auto &pv : this->Pvs_list) {
        if (pv.getPvname() == "kebab3") {
            QMultiMap<QString, QPair<QString, QString>> map = pv.getPvmessages();
            if (map.size() == 0) {
                qDebug() << "No messages in Pv " << pv.getPvname();
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
void PvRepository::WritePvsmessages() {
    // Create a file for each Pv and add their messages to them
    QString filename;
    QString homeDir = QDir::homePath();
    QDir PvDir(homeDir + QDir::separator() + "Pv");
    if (!PvDir.exists()) {
        PvDir.mkpath(".");
    }
    qDebug() << Pvs_list.size();
    for (const auto& p : Pvs_list) {
        filename = PvDir.filePath(p.getPvname() + ".json");
        QFile file(filename);
        if (file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
            QJsonArray messageArray;
            for (QMultiMap<QString, QPair<QString, QString>>::const_iterator it = p.getPvmessages().constBegin(); it != p.getPvmessages().constEnd(); ++it) {
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
void PvRepository::ReadPvsmessages() {
    try {
        // Create a directory for the Pv files, if it doesn't already exist
        QString homeDir = QDir::homePath();
        QDir PvsDir(homeDir + QDir::separator() + "Pv");
        if (!PvsDir.exists()) {
            PvsDir.mkpath(".");
        }

        // Get a list of all the JSON files in the directory
        QStringList filters;
        filters << "*.json";
        QStringList PvFiles = PvsDir.entryList(filters, QDir::Files);

        // Read each Pv file and create a Pv object from its data
        for (const QString& PvFile : PvFiles) {
            QString PvName = PvFile.left(PvFile.lastIndexOf(".json"));
            Pv p(PvName);

            QString filename = PvsDir.filePath(PvFile);
            QFile file(filename);

            if (file.open(QIODevice::ReadOnly)) {
                QJsonDocument PvDoc = QJsonDocument::fromJson(file.readAll());
                QJsonArray messageArray = PvDoc.array();

                for (int i = 0; i < messageArray.size(); ++i) {
                    QJsonObject messageObj = messageArray.at(i).toObject();
                    QString timestamp = messageObj.value("timestamp").toString();
                    QString message = messageObj.value("message").toString();
                    QString src = messageObj.value("src").toString();
                    p.setPvmessages(src, message, timestamp);
                }

                Pvs_list.append(p);
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
        qDebug() << "Error reading Pv files: " << e.message() << " (" << e.code() << ")";
    }
}


//removes client directory & its files after logout
void PvRepository::RemovePvsDir(){
    try {
        QString homeDir = QDir::homePath();
        QDir PvsDir(homeDir + QDir::separator() + "Pv");

        // Remove all the files in the directory
        QFileInfoList fileList = PvsDir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden | QDir::Files);
        for (const QFileInfo& fileInfo : fileList) {
            if (!fileInfo.dir().remove(fileInfo.fileName())) {
                QString message = "Could not remove file " + fileInfo.absoluteFilePath();
                QString code = "NO_Pv_FILE";
                throw ExceptionHandler(message, code);
            }
        }

        // Remove the directory itself
        if (!PvsDir.rmdir(".")) {
            QString message = "Could not remove directory " + PvsDir.absolutePath();
            QString code = "NO_Pv_DIRECTORY";
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

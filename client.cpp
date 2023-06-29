#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDir>
#include <QFile>
#include <QByteArray>
#include <QStandardPaths>
#include "client.h"
#include "httphandler.h"
#include "urlmaker.h"
#include "exceptionhandler.h"

//default constructor
Client::Client()
{}

//constructor of client class
Client::Client(QString username ,QString password ,QString firstname ,QString lastname)
{
    this->username = username;
    this->password = password;
    this->firstname = firstname;
    this->lastname = lastname;
}

Client::Client(QString username, QString password){
    this->username = username;
    this->password = password;
}

//getter Merhods
QString Client::getToken(){
    return token;
}

//setter Methods
void Client::setToken(QString token){
    this->token = token;
}

//lets the user signup in messenger
QPair<QString, QString> Client::Signup(){
    HttpHandler http;
    QString arguments;
    arguments = "username="+username+"&"+"password="+password+"&"+"firstname="+firstname+"&"+"lastname="+lastname;
    urlmaker newurl("signup", "token" , arguments);
    const QString url = newurl.generate();
    QString code , message;
    QPair<QJsonObject, bool> response = http.makeRequest(url);
    if(response.second){
        QJsonObject jsonObj = response.first;
        if (jsonObj.contains("code")){
            code = jsonObj.value("code").toString();
            if (code == "200"){
                message = jsonObj.value("message").toString();
                //Write to Json file

            }else if (code == "204") {
                QString message = jsonObj.value("message").toString();
                qDebug() <<message;
                //user already exists implement with gui
            }
        }
    }
    return qMakePair(code , message);
}

//lets the users login using their username and password
QPair<QString , QString> Client::Login() {
    //Request Example: http://api.barafardayebehtar.ml:8080/login?username=sara&password=1234
    QString arguments = "username="+username+"&password="+password;
    urlmaker login_url("login" , arguments);
    const QString url = login_url.generate();
    QString code , message;
    HttpHandler http;
    QPair<QJsonObject, bool> response = http.makeRequest(url);

    if (response.second) {
        QJsonObject jsonObj = response.first;
        message = jsonObj.value("message").toString();
        code = jsonObj.value("code").toString();
                if (jsonObj.contains("message") && jsonObj.contains("code")) {
                 QString message = jsonObj.value("message").toString();
                 QString code = jsonObj.value("code").toString();
                    if(message ==  "Logged in Successfully" && code == "200"){
                        QString token = jsonObj.value("token").toString();
                        setToken(token);
                        qDebug()<<"token assigned"<< token;
                    }
                }
    }
    else {
        qDebug() << "Error: Request was not successful";
    }
    WriteClient();
    return qMakePair(code , message);
}


//lets the user logout of messenger client
void Client::Logout(){
        QString arguments = "username="+this->username+"&password="+this->password;
        urlmaker login_url("logout" , arguments);
        const QString url = login_url.generate();
        HttpHandler http;
        QPair<QJsonObject, bool> response = http.makeRequest(url);
            if (response.second) {
                QJsonObject jsonObj = response.first;

                QString token = jsonObj.value("token").toString();
                qDebug() << "token:" << token;
                if (jsonObj.contains("message")) {
                    QString message = jsonObj.value("message").toString();
                    qDebug() << "Message:" << message;
                } else {
                    qDebug() << "Message key not found in JSON object";
                }
                if (jsonObj.contains("code")) {
                    QString code = jsonObj.value("code").toString();
                    qDebug() << "Code:" << code;
                } else {
                    qDebug() << "Code key not found in JSON object";
                }
            } else {
                qDebug() << "Error: Request was not successful";
            }
}

//Writes Client data to a file
void Client::WriteClient(){
            try{
                Client flag;
                flag.ReadClient();
                if (flag.username == this->username && flag.password == this->password) {
                    // Create the flag JSON data
                    QJsonObject flagObj;
                    flagObj.insert("username", flag.username);
                    flagObj.insert("password", flag.password);
                    flagObj.insert("firstname", flag.firstname);
                    flagObj.insert("lastname", flag.lastname);
                    flagObj.insert("token", this->token);
                    QJsonDocument flagDoc(flagObj);
                    QString homeDir = QDir::homePath();
                    QDir clientDir(homeDir + QDir::separator() + "client");
                    QString filename = clientDir.filePath(username + ".json");
                    QFile file(filename);
                    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
                        file.write(flagDoc.toJson());
                        file.close();
                    }
                }
                else {
                // If the username and password do not match, create a new file
                // Create a JSON object from the client data
                QJsonObject clientObj;
                clientObj.insert("username", username);
                clientObj.insert("password", password);
                clientObj.insert("firstname", firstname);
                clientObj.insert("lastname", lastname);
                clientObj.insert("token",token);
                // Convert the JSON object to a document
                QJsonDocument clientDoc(clientObj);
                // Create a directory for the client files, if it doesn't already exist
                QString homeDir = QDir::homePath();
                QDir clientDir(homeDir + QDir::separator() + "client");
                if (!clientDir.exists()) {
                    clientDir.mkpath(".");
                }
                // Write the client data to a file
                QString filename = clientDir.filePath(username + ".json");
                QFile file(filename);
                if (file.open(QIODevice::WriteOnly)) {
                    file.write(clientDoc.toJson());
                    file.close();
                }
                else {
                    // Throw an exception if the file could not be opened for writing
                    QString message = "Could not open file " + filename + " for writing";
                    QString code = "FILE_OPEN_ERROR";
                    throw HttpHandlerException(message, code);
                }
            }
        }
            catch (const HttpHandlerException& e) {
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

//Reads Client data from a file
void Client::ReadClient() {
            try {
                // Get the path to the client file
                QString homeDir = QDir::homePath();
                QDir clientDir(homeDir + QDir::separator() + "client");
                QStringList filters;
                filters << "*.json";
                QFileInfoList fileInfoList = clientDir.entryInfoList(filters, QDir::Files);
                if (fileInfoList.isEmpty()) {
                    // Throw an exception if no client files were found
                    QString message = "No client files found in directory " + clientDir.absolutePath();
                    QString code = "NO_CLIENT_FILES";
                    throw HttpHandlerException(message, code);
                }
                QString filename = fileInfoList.first().absoluteFilePath();
                // Read the client data from the file
                QFile file(filename);
                if (file.open(QIODevice::ReadOnly)) {
                    QJsonDocument clientDoc = QJsonDocument::fromJson(file.readAll());
                    QJsonObject clientObj = clientDoc.object();
                    // Update the client data
                    this->username = clientObj.value("username").toString();
                    this->password = clientObj.value("password").toString();
                    this->firstname = clientObj.value("firstname").toString();
                    this->lastname = clientObj.value("lastname").toString();
                    this->token = clientObj.value("token").toString();
                    file.close();
                }
                qDebug() << "Read!";
            } catch (const HttpHandlerException& e) {
                // Handle the exception
                qDebug() << "Error: " << e.message() << " (" << e.code() << ")";
                // Re-throw the exception to propagate it further up the call stack
                throw;
            } catch (...) {
                // Handle any other exceptions
                qDebug() << "Unknown error occurred";
            }
}

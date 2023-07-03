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
QString Client::getUsername(){
    return username;
}
QString Client::getPassword(){
    return password;
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
        message = jsonObj.value("message").toString();
        code = jsonObj.value("code").toString();
        if (jsonObj.contains("message") && jsonObj.contains("code")){
            if (message ==  "Signed Up Successfully" && code == "200"){
                message = jsonObj.value("message").toString();
                qDebug() <<message << "code : " << code;
                WriteClient();
            }
            else if (code != "200") {
                qDebug() <<message << "Error code : " << code;
                //user already exists implement with gui
            }
        }
    }
    return qMakePair(code , message);
}

//lets the users login using their username and password
QPair<QString , QString> Client::Login() {
    //Request Example: http://api.barafardayebehtar.ml:8080/login?username=sara&password=1234
    QString arguments = "username="+this->username+"&password="+this->password;
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
                    if(message ==  "Logged in Successfully" && code == "200"){
                        QString token = jsonObj.value("token").toString();
                        setToken(token);
                        qDebug() <<message << "code : " << code;
                        qDebug()<<"token assigned :"<< token;
                        WriteClient();
                    }
                    else if (code != "200") { //handled by UI
                        qDebug() <<message << "Error code : " << code;
                    }
                }
    }
    return qMakePair(code , message);
}


//lets the user logout of messenger client
QPair<QString , QString> Client::Logout(){
    QString arguments = "username="+this->username+"&password="+this->password;
    urlmaker login_url("logout" , arguments);
    const QString url = login_url.generate();
    HttpHandler http;
    QString code , message;
    QPair<QJsonObject, bool> response = http.makeRequest(url);
        if (response.second) {
            QJsonObject jsonObj = response.first;
            message = jsonObj.value("message").toString();
            code = jsonObj.value("code").toString();
            if (jsonObj.contains("message") && jsonObj.contains("code")) {
                if(message ==  "Logged Out Successfully" && code == "200"){
                qDebug() <<message << "code : " << code;
                }
                else if (code != "200") {
                QString code = jsonObj.value("code").toString();
                qDebug() << "Code:" << code;
                }
            }
        }
    RemoveClientDir();
    return qMakePair(code ,message);
}


//Writes Client data to a file
void Client::WriteClient(){
        try{
            Client flag;
            flag.ReadClient();
            //handles the state where client has just signed up and wants to try to log in
            if (flag.username == this->username && flag.password == this->password) {
                // Create the flag JSON data
                QJsonObject flagObj;
                flagObj.insert("username", flag.username);
                flagObj.insert("password", flag.password);
                flagObj.insert("firstname", flag.firstname);
                flagObj.insert("lastname", flag.lastname);
                flagObj.insert("token", this->token);
                // Convert the JSON object to a document
                QJsonDocument flagDoc(flagObj);
                QString homeDir = QDir::homePath();
                QDir clientDir(homeDir + QDir::separator() + "Clients");
                QString filename = clientDir.filePath(username + ".json");
                QFile file(filename);
                if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
                    file.write(flagDoc.toJson());
                    file.close();
                }
                else {
                    // Throw an exception if the file could not be opened for writing
                    QString message = "Could not open file " + filename + " for writing";
                    QString code = "FILE_OPEN_ERROR";
                    throw ExceptionHandler(message, code);
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
            QDir clientDir(homeDir + QDir::separator() + "Clients");
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

//Reads Client data from a file
void Client::ReadClient() {
        try {
            // Get the path to the client file
            QString homeDir = QDir::homePath();
            QDir clientDir(homeDir + QDir::separator() + "Clients");
            if (!clientDir.exists()) {
                // Throw an exception if the Directory was not found or made
                QString message = "Could not Make/Find Directory: " + clientDir.absolutePath() + " for writing";
                QString code = "NO_CLIENT_DIRECTORY";
                throw ExceptionHandler(message, code);
            }
            // Get a list of all the JSON files in the directory
            QStringList filters;
            filters << "*.json";
            QFileInfoList fileInfoList = clientDir.entryInfoList(filters, QDir::Files);
            if (fileInfoList.isEmpty()) {
                // Throw an exception if no client files were found
                this->token = "";
                QString message = "No client files found in directory " + clientDir.absolutePath();
                QString code = "NO_CLIENT_FILES";
                throw ExceptionHandler(message, code);
                return;
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
            else {
                // Throw an exception if the file could not be opened for reading
                this->token = "";
                QString message = "Could not open file " + filename + " for reading";
                QString code = "FILE_OPEN_ERROR";
                throw ExceptionHandler(message, code);
            }
        }
         catch (const ExceptionHandler& e) {
            // Handle the exception
            qDebug() << "Error: " << e.message() << " (" << e.code() << ")";
            // Re-throw the exception to propagate it further up the call stack
            //throw;
        } catch (...) {
            // Handle any other exceptions
            qDebug() << "Unknown error occurred";
        }
}

//removes client directory & its files after logout
void Client::RemoveClientDir() {
        try {
            QString homeDir = QDir::homePath();
            QDir clientDir(homeDir + QDir::separator() + "Clients");
            QString filename = clientDir.filePath(username + ".json");

            QFile file(filename);
            if (file.exists()) {
                if (!file.remove()) {
                throw ExceptionHandler("Could not remove client file", filename);
                }
            }
        }
        catch (const ExceptionHandler& e) {
            // Handle the exception
            qDebug() << "Error: " << e.message() << " (" << e.code() << ")";
            // Re-throw Here if needed
            //                throw;
        } catch (...) {
            // Handle any other exceptions
            qDebug() << "Unknown error occurred";
        }
}

//Checks the State of the User at Program startup
void Client::ClientState(){
        ReadClient();
        if(token != ""){
            //do sth
        }
        else{
            //do sth
        }
}

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "mainwindow.h"
#include "httphandler.h"
#include "urlmaker.h"
#include "client.h"
#include "exceptionhandler.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
//    HttpHandler http;
////    QString arguments = "username=sara&password=1234&firstname=sara&lastname=baradaran";
////    urlmaker newurl("signup" , "token" , arguments);
////    const QString url = newurl.generate();
//    QString arguments = "username=sara&password=1234&firstname=sara&lastname=baradaran";
//    urlmaker newurl("login" , arguments);
//    const QString url = newurl.generate();
  
////    Client newuser("kebab4", "6kebab", "kebabist", "jooj");
////    newuser.Signup();
////    Client cl("kebab","6kebab","kebab","kebab");
////    cl.Login("kebab4","6kebab");
////    group newgroup("newgroup", "mygroup");
////    newgroup.create(cl);
////        Client cl("kebab","6kebab","kebab","kebab");
////        cl.Logout("kebab","6kebab");
//        try {
//            QPair<QJsonObject, bool> response = http.makeRequest(url);
//            QJsonObject jsonObj = response.first;
//           QString message = jsonObj.value("message").toString();
//            qDebug() << "Message:" << message;
//           QString code = jsonObj.value("code").toString();
//            qDebug() << "Code:" << code;
//        } catch (const HttpHandlerException &e) {
//            // Handle the exception here
//            QString errorMessage = "Message: " + e.message() + "\nCode: " + e.code();
//            qDebug() << "error:" << errorMessage;
//        }
//    QString arguments = "username=kebab&password=6kebab";
//    urlmaker login_url("logout" , arguments);
//    const QString url = login_url.generate();

//    QPair<QJsonObject, bool> response = http.makeRequest(url);
//    if (response.second) {
//        QJsonObject jsonObj = response.first;

//        QString token = jsonObj.value("token").toString();
//        qDebug() << "token:" << token;
//        if (jsonObj.contains("message")) {
//            QString message = jsonObj.value("message").toString();
//            qDebug() << "Message:" << message;
//        } else {
//            qDebug() << "Message key not found in JSON object";
//        }
//        if (jsonObj.contains("code")) {
//            QString code = jsonObj.value("code").toString();
//            qDebug() << "Code:" << code;
//        } else {
//            qDebug() << "Code key not found in JSON object";
//        }
//    } else {
//        qDebug() << "Error: Request was not successful";
//    }
//    HttpHandler http;
//    QString arguments = "username=sara&password=1234&firstname=sara&lastname=baradaran";
//    urlmaker newurl("signup" , "token" , arguments);
//    const QString url = newurl.generate();
//    http.makeRequest(url);
    //Client newuser("kebab", "6kebab", "kebabist", "jooj");
    //newuser.Signup();
//    Client newuser("kebab", "6kebab", "kebabist", "jooj");
//    newuser.Signup();
        MainWindow w;
        w.show();
    return app.exec();
}


#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QThread>
#include "mainwindow.h"
#include "httphandler.h"
#include "urlmaker.h"
#include "client.h"
#include "group.h"
#include "exceptionhandler.h"
#include "grouprepository.h"



int main(int argc, char *argv[])
{
//    QApplication app(argc, argv);
//    GroupRepository gr;
//    Client cl("kebab","6kebab","kebab","kebab");
////    gr.create(cl);
//    HttpHandler http;
////    QString arguments = "username=sara&password=1234&firstname=sara&lastname=baradaran";
////    urlmaker newurl("signup" , "token" , arguments);
////    const QString url = newurl.generate();
//    QString arguments = "username=sara&password=1234&firstname=sara&lastname=baradaran";
//    urlmaker newurl("login" , arguments);
//    const QString url = newurl.generate();
//    http.makeRequest(url);
//    cl.Logout("kebab","6kebab");
//    cl.Login("kebab","6kebab");
//    //gr.createGroup(cl , "new");
//    //gr.joinGroup(cl , "new");
//    gr.getGroupchats(cl , "lmao" , "");
//////    Client newuser("kebab4", "6kebab", "kebabist", "jooj");
//////    newuser.Signup();
//////    cl.Login("kebab4","6kebab");
//////    group newgroup("newgroup", "mygroup");
//////    newgroup.create(cl);
//////        Client cl("kebab","6kebab","kebab","kebab");
//////        cl.Logout("kebab","6kebab");

//            QPair<QJsonObject, bool> response = http.makeRequest(url);
//            QJsonObject jsonObj = response.first;
//           QString message = jsonObj.value("message").toString();
//            qDebug() << "Message:" << message;
//           QString code = jsonObj.value("code").toString();
//            qDebug() << "Code:" << code;

QApplication app(argc, argv);
//GroupRepository gr;
//Client cl("kebab","6kebab","kebab","kebab");
//cl.Logout("kebab","6kebab");
//cl.Login("kebab","6kebab");
//cl.WriteClient();
HttpHandler http;
Client cl("kebab11dsf11","1111sdfkebab","kebab","kebab");
QPair<QJsonObject, bool> response = http.makeRequest("http://invalidurl.com");

//cl.Signup();
//cl.RemoveClientDir();
//cl.ReadClient();
//QPair<QString , QString> response =cl.Login();

//cl.Logout();
//gr.createGroup(cl , "nmdvaghean9");
//QThread::msleep(20000);
//gr.getGroupchats(cl,"nmdvaghean9","");
//gr.display();

//GroupRepository gr;
//Group g("Group1","lmao");

//gr.createGroup(cl , "nah123123");
//gr.joinGroup(cl , "nah123123");
//gr.sendmessageGroup("lmao", "just sent a message" , cl);
//gr.getGrouplist(cl);
////gr.getGroupchats(cl,"lmao","20230628212852");
//gr.display();


//gr.display();
//    QString arguments = "username=kebab&password=6kebab";
//    urlmaker login_url("logout" , arguments);
//    const QString url = login_url.generate();

//    QPair<QJsonObject, bool> response = http.makeRequest(url);
    if (!response.second) {
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
//    HttpHandler http;
//    QString arguments = "username=sara&password=1234&firstname=sara&lastname=baradaran";
//    urlmaker newurl("signup" , "token" , arguments);
//    const QString url = newurl.generate();
//    http.makeRequest(url);
    //Client newuser("kebab", "6kebab", "kebabist", "jooj");
    //newuser.Signup();
//    Client newuser("kebab", "6kebab", "kebabist", "jooj");
//    newuser.Signup();

    return app.exec();
}


#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "httphandler.h"
#include "urlmaker.h"
#include "client.h"
#include "group.h"
//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);

//    QTranslator translator;
//    const QStringList uiLanguages = QLocale::system().uiLanguages();
//    for (const QString &locale : uiLanguages) {
//        const QString baseName = "AP_Messenger_Project_" + QLocale(locale).name();
//        if (translator.load(":/i18n/" + baseName)) {
//            a.installTranslator(&translator);
//            break;
//        }
//    }
//    MainWindow w;
//    w.show();
//    return a.exec();
//}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
//    HttpHandler http;
//    QString arguments = "username=sara&password=1234&firstname=sara&lastname=baradaran";
//    urlmaker newurl("signup" , "token" , arguments);
//    const QString url = newurl.generate();
//    QString arguments = "username=sara&password=1234&firstname=sara&lastname=baradaran";
//    urlmaker newurl("signup" , arguments);
//    const QString url = newurl.generate();

    Client newuser("kebab4", "6kebab", "kebabist", "jooj");
    newuser.Signup();
    Client cl("kebab","6kebab","kebab","kebab");
    cl.Login("kebab4","6kebab");
    group newgroup("newgroup", "mygroup");
    newgroup.create(cl);
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

    return app.exec();
}


//int main(int argc, char *argv[])
//{
//    QCoreApplication app(argc, argv);
//    HttpHandler http;
//    QString arguments = "username=sara&password=1234&firstname=sara&lastname=baradaran";
//    urlmaker newurl("signup" , "token" , arguments);
//    const QString url = newurl.generate();
//    const QJsonObject jsonObj= http.makeRequest(url);

//    QString message = jsonObj.value("message").toString();
//    QString code = jsonObj.value("code").toString();
//    qDebug() << "message:" << message << ", code: " << code << Qt::endl;
//    return app.exec();
//}

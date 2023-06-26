#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "httphandler.h"
#include "urlmaker.h"
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
    QCoreApplication app(argc, argv);
    HttpHandler http;
    QString arguments = "username=sara&password=1234&firstname=sara&lastname=baradaran";
    urlmaker newurl("signup" , "token" , arguments);
    const QString url = newurl.generate();
    http.makeRequest(url);

    return app.exec();
}

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QThread>
#include <QPointer>
#include <QProcess>
#include "mainwindow.h"
#include "client.h"
#include "grouprepository.h"
#include "channelrepository.h"
#include "pvrepository.h"


int main(int argc, char *argv[]){
    int result = 0;
    try{
        QApplication app(argc, argv);
        Client client;
        GroupRepository groupRepo;
        ChannelRepository channelRepo;
        PvRepository pvRepo;
        MainWindow w(client ,groupRepo , channelRepo , pvRepo);
        result = app.exec();
         //Restart the application if the exit code is 42
        if (result == 42) {
        QProcess::startDetached(QApplication::applicationFilePath(), QApplication::arguments());
        }
    }catch (...) {
         qDebug() << "Unknown exception caught in mainwindow";
    }

    return result;
}

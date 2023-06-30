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
#include "channel.h"
#include "channelrepository.h"
#include "pvrepository.h"
#include "pv.h"



int main(int argc, char *argv[]){
QApplication app(argc, argv);

////test pv
////the tester is kebab2
////the other user is kebab3
//Client cl;
//Pv p("kebab3");
//PvRepository pr;
////pr.sendmessagePv("kebab3","salam da",cl);
//pr.getPvlist(cl);
////pr.getPvchats(cl,"kebab3","");
////pr.WritePvsmessages();

//pr.ReadPvsmessages();
//QList<Pv> List = pr.getPv_list();
//qDebug() << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!: ";
//for (const Pv& Pv : List) {
//    qDebug() << "Channel Name: " << Pv.getPvname();
//    qDebug() << "Messages: ";
//    const QMultiMap<QString, QPair<QString, QString>>& messages = Pv.getPvmessages();
//    for (auto it = messages.constBegin(); it != messages.constEnd(); ++it) {

////        QString timestamp = it.key();
////        QString src = it.value().first;
////        QString message = it.value().second;

////        qDebug() << "Sender: " << src << ", Text: " << message << ", Date: " << timestamp;
//qDebug() << "Time: " << it.key() << ", sender: " << it.value().first << ", text" << it.value().second;
//    }
//    }

//pr.RemovePvsDir();

Client cl1("kebab","6kebab","kebab","kebab");

GroupRepository groupRepo;
//groupRepo.getGrouplist("41c0089068b863e6a14ccc5d6dcda514");
//groupRepo.getGroupchats("41c0089068b863e6a14ccc5d6dcda514","lmao","");
//groupRepo.WriteGroupsmessages();
//groupRepo.createGroup("41c0089068b863e6a14ccc5d6dcda514","ahhhhhhhhhhhert");
groupRepo.joinGroup("852e7892429df7577d95a410ca9d38ff","ahhhhhhhhhhhert");
groupRepo.sendmessageGroup("852e7892429df7577d95a410ca9d38ff","ahhhhhhhhhhhert","eyyyyyyy baba");
//groupRepo.ReadGroupsmessages();
//const std::vector<std::unique_ptr<Group>>& groupList = groupRepo.getGroup_list();
//for (const auto& groupPtr : groupList) {
//    qDebug() << "Group Name: " << groupPtr->getGroupname();
//    qDebug() << "Messages: ";
//    const QMultiMap<QString, QPair<QString, QString>>& messages = groupPtr->getGroupmessages();
//    for (auto it = messages.constBegin(); it != messages.constEnd(); ++it) {
//        qDebug() << "Time: " << it.key() << ", sender: " << it.value().first << ", text" << it.value().second;
//    }
//}
ChannelRepository cr;

cr.getChannellist(cl1);
//cr.getChannelchats(cl1,"nmdvaghean9","");
//cr.WriteChannelsmessages();

cr.ReadChannelsmessages();
QList<Channel> cList = cr.getChannel_list();
for (const Channel& chan : cList) {
    qDebug() << "channel Name: " << chan.getChannelname();
    qDebug() << "Messages: ";
    const QMultiMap<QString, QPair<QString, QString>>& messages = chan.getChannelmessages();
    for (auto it = messages.constBegin(); it != messages.constEnd(); ++it) {
      qDebug() << "Time: " << it.key() << ", sender: " << it.value().first << ", text" << it.value().second;
    }
}
    return app.exec();
}


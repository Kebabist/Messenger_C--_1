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
Client cl1("kebab","6kebab","kebab","kebab");

//PvRepository pr;

GroupRepository groupRepo;
//groupRepo.getGrouplist("41c0089068b863e6a14ccc5d6dcda514");
//groupRepo.getGroupchats("41c0089068b863e6a14ccc5d6dcda514","lmao","");
//groupRepo.WriteGroupsmessages();
//groupRepo.createGroup("41c0089068b863e6a14ccc5d6dcda514","ahhhhhhhhhhhert");
//groupRepo.joinGroup("852e7892429df7577d95a410ca9d38ff","ahhhhhhhhhhhert");
//groupRepo.sendmessageGroup("852e7892429df7577d95a410ca9d38ff","ahhhhhhhhhhhert","eyyyyyyy baba");

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
//cr.joinChannel("41c0089068b863e6a14ccc5d6dcda514","lmaochannel");
//cr.joinChannel("41c0089068b863e6a14ccc5d6dcda514","new");
//cr.createChannel("41c0089068b863e6a14ccc5d6dcda514","yuhahahahaha");
//cr.sendmessageChannel("41c0089068b863e6a14ccc5d6dcda514","yuhahahahaha","salam Alekom");
//cr.sendmessageChannel("41c0089068b863e6a14ccc5d6dcda514","yuhahahahaha","alakom salam");
//cr.sendmessageChannel("41c0089068b863e6a14ccc5d6dcda514","yuhahahahaha","oh yeaaaah");
cr.getChannellist("41c0089068b863e6a14ccc5d6dcda514");
cr.getChannelchats("41c0089068b863e6a14ccc5d6dcda514","lmaochannel","");
cr.getChannelchats("41c0089068b863e6a14ccc5d6dcda514","new","");
cr.getChannelchats("41c0089068b863e6a14ccc5d6dcda514","yuhahahahaha","");
cr.WriteChannelsmessages();
//cr.RemoveChannelsDir();
cr.ReadChannelsmessages();
const std::vector<std::unique_ptr<Channel>>& channelList = cr.getChannel_list();
for (const auto& channelPtr : channelList) {
    qDebug() << "Group Name: " << channelPtr->getChannelname();
    qDebug() << "Messages: ";
    const QMultiMap<QString, QPair<QString, QString>>& messages = channelPtr->getChannelmessages();

//the other person is kebab4
//the given toke is for kebab3
PvRepository pvRepo;
pvRepo.getPvlist("11d02f67196f529abc0e227d11d14fa3");
pvRepo.getPvchats("11d02f67196f529abc0e227d11d14fa3","kebab4","");
pvRepo.getPvchats("11d02f67196f529abc0e227d11d14fa3","kebab2","");
pvRepo.WritePvsmessages();
pvRepo.sendmessagePv("11d02f67196f529abc0e227d11d14fa3","kebab4","eyyyyyyy baba");
pvRepo.ReadPvsmessages();
const std::vector<std::unique_ptr<Pv>>& pvList = pvRepo.getPv_list();
for (const auto& pvPtr : pvList) {
    qDebug() << "Group Name: " << pvPtr->getPvname();
    qDebug() << "Messages: ";
    const QMultiMap<QString, QPair<QString, QString>>& messages = pvPtr->getPvmessages();
    for (auto it = messages.constBegin(); it != messages.constEnd(); ++it) {
        qDebug() << "Time: " << it.key() << ", sender: " << it.value().first << ", text" << it.value().second;
    }
}
  
return app.exec();
}


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
#include "repository.h"



int main(int argc, char *argv[]){
QApplication app(argc, argv);
Client cl1("kebab","6kebab","kebab","kebab");

GroupRepository groupRepo;

//groupRepo.getList("41c0089068b863e6a14ccc5d6dcda514");
//groupRepo.getChats("41c0089068b863e6a14ccc5d6dcda514","lmao","");
//groupRepo.getChats("41c0089068b863e6a14ccc5d6dcda514","new","");
//groupRepo.create("852e7892429df7577d95a410ca9d38ff","testingnewimp");
//groupRepo.join("41c0089068b863e6a14ccc5d6dcda514","testingnewimp");
//groupRepo.sendMessage("41c0089068b863e6a14ccc5d6dcda514","testingnewimp","eyyyyyyy baba");
//groupRepo.sendMessage("41c0089068b863e6a14ccc5d6dcda514","testingnewimp","eyyyyyyy baba2");
//groupRepo.getChats("41c0089068b863e6a14ccc5d6dcda514","testingnewimp","");
//groupRepo.getChats("41c0089068b863e6a14ccc5d6dcda514","ahhhhhhsfsdhhh546456hhert","");
//groupRepo.getChats("41c0089068b863e6a14ccc5d6dcda514","ahhhhhhhhhhhert","");
//groupRepo.getChats("41c0089068b863e6a14ccc5d6dcda514","ahhhhhhhhhhhert","");
//groupRepo.writeMessages();
//groupRepo.join("852e7892429df7577d95a410ca9d38ff","ahhhhhhsfsdhhh546456hhert");
//qDebug()<<"=======================================";
//groupRepo.readMessages();
//const std::vector<std::unique_ptr<DTO>>& groupList = groupRepo.Repository::getList();
//for (const auto& groupPtr : groupList) {
//    qDebug() << "Group Name: " << groupPtr->getName();
//    qDebug() << "Messages: ";
//    const QMultiMap<QString, QPair<QString, QString>>& messages = groupPtr->getMessages();
//    for (auto it = messages.constBegin(); it != messages.constEnd(); ++it) {
//        qDebug() << "Time: " << it.key() << ", sender: " << it.value().first << ", text" << it.value().second;
//    }
//}
groupRepo.removeDir();



ChannelRepository cr;
//cr.joinChannel("41c0089068b863e6a14ccc5d6dcda514","lmaochannel");
//cr.joinChannel("41c0089068b863e6a14ccc5d6dcda514","new");
//cr.createChannel("41c0089068b863e6a14ccc5d6dcda514","yuhahahahaha");
//cr.sendmessageChannel("41c0089068b863e6a14ccc5d6dcda514","yuhahahahaha","salam Alekom");
//cr.sendmessageChannel("41c0089068b863e6a14ccc5d6dcda514","yuhahahahaha","alakom salam");
//cr.sendmessageChannel("41c0089068b863e6a14ccc5d6dcda514","yuhahahahaha","oh yeaaaah");
//cr.getChannellist("41c0089068b863e6a14ccc5d6dcda514");
//cr.getChannelchats("41c0089068b863e6a14ccc5d6dcda514","lmaochannel","");
//cr.getChannelchats("41c0089068b863e6a14ccc5d6dcda514","new","");
//cr.getChannelchats("41c0089068b863e6a14ccc5d6dcda514","yuhahahahaha","");
//cr.WriteChannelsmessages();
//cr.RemoveChannelsDir();
//cr.ReadChannelsmessages();
//const std::vector<std::unique_ptr<Channel>>& channelList = cr.getChannel_list();
//for (const auto& channelPtr : channelList) {
//    qDebug() << "Channel Name: " << channelPtr->getName();
//    qDebug() << "Messages: ";
//    const QMultiMap<QString, QPair<QString, QString>>& messages = channelPtr->getMessages();
//    for (auto it = messages.constBegin(); it != messages.constEnd(); ++it) {
//        qDebug() << "Time: " << it.key() << ", sender: " << it.value().first << ", text" << it.value().second;
//    }
//}

//the other person is kebab4
//the given token is for kebab3
PvRepository pvRepo;
Pv pv;
pvRepo.getList("11d02f67196f529abc0e227d11d14fa3");
pvRepo.getChats("11d02f67196f529abc0e227d11d14fa3","kebab4","20230701121345");
pvRepo.getChats("11d02f67196f529abc0e227d11d14fa3","kebab2","20230630170702");
pvRepo.writeMessages();
pvRepo.sendMessage("11d02f67196f529abc0e227d11d14fa3","kebab4","alan ferestadam");
pvRepo.readMessages();
const std::vector<std::unique_ptr<DTO>>& pvList = pvRepo.Repository::getList();
for (const auto& pvPtr : pvList) {
    qDebug() << "Pv Name: " << pvPtr->getName();
    qDebug() << "Messages: ";
    const QMultiMap<QString, QPair<QString, QString>>& messages = pvPtr->getMessages();
    for (auto it = messages.constBegin(); it != messages.constEnd(); ++it) {
        qDebug() << "Time: " << it.key() << ", sender: " << it.value().first << ", text" << it.value().second;
    }
}
pvRepo.removeDir();
return app.exec();
}

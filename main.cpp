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
Client cl("kebab","6kebab","kebab","kebab");
QPair<QString , QString> q = cl.Login();
cl.WriteClient();
//cl.RemoveClientDir();
GroupRepository groupRepo;

groupRepo.getList("5d67612b24aad42a25c03f058d1994f6");
groupRepo.getChats("5d67612b24aad42a25c03f058d1994f6","lmao","");
groupRepo.getChats("5d67612b24aad42a25c03f058d1994f6","new","");
//groupRepo.create("852e7892429df7577d95a410ca9d38ff","testingnewimp");
//groupRepo.join("41c0089068b863e6a14ccc5d6dcda514","testingnewimp");
//groupRepo.sendMessage("41c0089068b863e6a14ccc5d6dcda514","testingnewimp","eyyyyyyy baba");
//groupRepo.sendMessage("41c0089068b863e6a14ccc5d6dcda514","testingnewimp","eyyyyyyy baba2");
//groupRepo.getChats("41c0089068b863e6a14ccc5d6dcda514","testingnewimp","");
//groupRepo.getChats("41c0089068b863e6a14ccc5d6dcda514","ahhhhhhsfsdhhh546456hhert","");
//groupRepo.getChats("41c0089068b863e6a14ccc5d6dcda514","ahhhhhhhhhhhert","");
//groupRepo.getChats("41c0089068b863e6a14ccc5d6dcda514","ahhhhhhhhhhhert","");
groupRepo.writeMessages();
//groupRepo.join("852e7892429df7577d95a410ca9d38ff","ahhhhhhsfsdhhh546456hhert");
//qDebug()<<"=======================================";
groupRepo.readMessages();
const std::vector<std::unique_ptr<DTO>>& groupList = groupRepo.Repository::getList();
for (const auto& groupPtr : groupList) {
    qDebug() << "Group Name: " << groupPtr->getName();
    qDebug() << "Messages: ";
    const QMultiMap<QString, QPair<QString, QString>>& messages = groupPtr->getMessages();
    for (auto it = messages.constBegin(); it != messages.constEnd(); ++it) {
        qDebug() << "Time: " << it.key() << ", sender: " << it.value().first << ", text" << it.value().second;
    }
}
//groupRepo.removeDir();



ChannelRepository cr;
//cr.join("41c0089068b863e6a14ccc5d6dcda514","lmaochannel");
//cr.joinChannel("41c0089068b863e6a14ccc5d6dcda514","new");
//cr.createChannel("41c0089068b863e6a14ccc5d6dcda514","yuhahahahaha");
//cr.sendMessage("41c0089068b863e6a14ccc5d6dcda514","yuhahahahaha","yay");
//cr.sendMessage("41c0089068b863e6a14ccc5d6dcda514","yuhahahahaha","nay");
//cr.sendMessage("41c0089068b863e6a14ccc5d6dcda514","yuhahahahaha","may");
cr.getList("5d67612b24aad42a25c03f058d1994f6");
cr.getChats("5d67612b24aad42a25c03f058d1994f6","lmaochannel","");
cr.getChats("5d67612b24aad42a25c03f058d1994f6","newchannel","");
cr.getChats("5d67612b24aad42a25c03f058d1994f6","yuhahahahaha","");
cr.writeMessages();
//cr.RemoveChannelsDir();
cr.readMessages();
const std::vector<std::unique_ptr<DTO>>& channelList = cr.Repository::getList();
for (const auto& channelPtr : channelList) {
    qDebug() << "Channel Name: " << channelPtr->getName();
    qDebug() << "Messages: ";
    const QMultiMap<QString, QPair<QString, QString>>& messages = channelPtr->getMessages();
    for (auto it = messages.constBegin(); it != messages.constEnd(); ++it) {
        qDebug() << "Time: " << it.key() << ", sender: " << it.value().first << ", text" << it.value().second;
    }
}

//the other person is kebab4
//the given token is for kebab3
PvRepository pvRepo;
//pvRepo.sendMessage("11d02f67196f529abc0e227d11d14fa3","kebab4","qwe");
//pvRepo.sendMessage("11d02f67196f529abc0e227d11d14fa3","kebab4","asd");
//pvRepo.sendMessage("11d02f67196f529abc0e227d11d14fa3","kebab4","zxc");
pvRepo.getList("11d02f67196f529abc0e227d11d14fa3");
pvRepo.getChats("11d02f67196f529abc0e227d11d14fa3","kebab4");
pvRepo.getChats("11d02f67196f529abc0e227d11d14fa3","kebab2","20230630170702");
pvRepo.writeMessages();
//pvRepo.sendMessage("11d02f67196f529abc0e227d11d14fa3","kebab4","alan ferestadam");
pvRepo.readMessages();
const std::vector<std::unique_ptr<DTO>>& pvList = pvRepo.Repository::getList();
for (const auto& pvPtr : pvList) {
    qDebug() << "Pv Name: " << pvPtr->getName();
    qDebug() << "Messages: ";
    const QMultiMap<QString, QPair<QString, QString>>& messages = pvPtr->getMessages();
}
//pvRepo.removeDir();


return app.exec();
}

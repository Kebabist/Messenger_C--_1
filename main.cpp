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
//cr.join("41c0089068b863e6a14ccc5d6dcda514","lmao");
//cr.join("41c0089068b863e6a14ccc5d6dcda514","newchannel");
//cr.create("41c0089068b863e6a14ccc5d6dcda514","yuhahahahaha");
cr.sendMessage("41c0089068b863e6a14ccc5d6dcda514","yuhahahahaha","123salam Alekom");
cr.sendMessage("41c0089068b863e6a14ccc5d6dcda514","yuhahahahaha","321alakom salam");
cr.sendMessage("41c0089068b863e6a14ccc5d6dcda514","yuhahahahaha","231oh yeaaaah");
cr.readMessages();
//cr.getList("41c0089068b863e6a14ccc5d6dcda514");
//cr.getChats("41c0089068b863e6a14ccc5d6dcda514","lmaochannel","");
//cr.getChats("41c0089068b863e6a14ccc5d6dcda514","newchannel","");
cr.getChats("41c0089068b863e6a14ccc5d6dcda514","yuhahahahaha","");
cr.writeMessages();
//cr.removeDir();

const std::vector<std::unique_ptr<DTO>>& channelList = cr.Repository::getList();
qDebug()<<"====================================";
for (const auto& channelPtr : channelList) {
    qDebug() << "Channel Name: " << channelPtr->getName();
    qDebug() << "Messages: ";
    const QMultiMap<QString, QPair<QString, QString>>& messages = channelPtr->getMessages();
    for (auto it = messages.constBegin(); it != messages.constEnd(); ++it) {
        qDebug() << "Time: " << it.key() << ", sender: " << it.value().first << ", text" << it.value().second;
    }
}
return app.exec();
}

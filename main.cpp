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

void updator(GroupRepository groupRepo , ChannelRepository channelRepo , PvRepository pvRepo ){
    const std::vector<std::unique_ptr<DTO>>& groupList = groupRepo.Repository::getList();
    const std::vector<std::unique_ptr<DTO>>& channelList = channelRepo.Repository::getList();
    const std::vector<std::unique_ptr<DTO>>& pvList = pvRepo.Repository::getList();
    emit (groupList , channelList , pvList);
}

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    Client cl1("kebab","6kebab","kebab","kebab");

    GroupRepository groupRepo;
    groupRepo.getList("6f72830134afcffe5fefba61c3216931");
    groupRepo.getChats("6f72830134afcffe5fefba61c3216931","lmao","");
    groupRepo.getChats("6f72830134afcffe5fefba61c3216931","new","");
    groupRepo.create("6f72830134afcffe5fefba61c3216931","testingnewimp");
    groupRepo.join("6f72830134afcffe5fefba61c3216931","testingnewimp");
    groupRepo.sendMessage("6f72830134afcffe5fefba61c3216931","testingnewimp","eyyyyyyy baba");
    groupRepo.sendMessage("6f72830134afcffe5fefba61c3216931","testingnewimp","eyyyyyyy baba2");
    groupRepo.getChats("6f72830134afcffe5fefba61c3216931","testingnewimp","");
    groupRepo.getChats("6f72830134afcffe5fefba61c3216931","ahhhhhhsfsdhhh546456hhert","");
    groupRepo.getChats("6f72830134afcffe5fefba61c3216931","ahhhhhhhhhhhert","");
    groupRepo.getChats("6f72830134afcffe5fefba61c3216931","ahhhhhhhhhhhert","");
    groupRepo.writeMessages();
    groupRepo.join("6f72830134afcffe5fefba61c3216931","ahhhhhhsfsdhhh546456hhert");
    qDebug()<<"=======================================";
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



    ChannelRepository channelRepo;
    channelRepo.join("6f72830134afcffe5fefba61c3216931","lmao");
    channelRepo.join("6f72830134afcffe5fefba61c3216931","newchannel");
    channelRepo.create("6f72830134afcffe5fefba61c3216931","yuhahahahaha");
    channelRepo.sendMessage("6f72830134afcffe5fefba61c3216931","yuhahahahaha","123salam Alekom");
    channelRepo.sendMessage("6f72830134afcffe5fefba61c3216931","yuhahahahaha","321alakom salam");
    channelRepo.sendMessage("6f72830134afcffe5fefba61c3216931","yuhahahahaha","231oh yeaaaah");
    channelRepo.readMessages();
    channelRepo.getList("6f72830134afcffe5fefba61c3216931");
    channelRepo.getChats("6f72830134afcffe5fefba61c3216931","lmaochannel","");
    channelRepo.getChats("6f72830134afcffe5fefba61c3216931","newchannel","");
    channelRepo.getChats("6f72830134afcffe5fefba61c3216931","yuhahahahaha","");
    channelRepo.writeMessages();
    const std::vector<std::unique_ptr<DTO>>& channelList = channelRepo.Repository::getList();
    qDebug()<<"====================================";
    for (const auto& channelPtr : channelList) {
        qDebug() << "Channel Name: " << channelPtr->getName();
        qDebug() << "Messages: ";
        const QMultiMap<QString, QPair<QString, QString>>& messages = channelPtr->getMessages();
        for (auto it = messages.constBegin(); it != messages.constEnd(); ++it) {
            qDebug() << "Time: " << it.key() << ", sender: " << it.value().first << ", text" << it.value().second;
        }
    }
    //cr.removeDir();


    //the other person is kebab4
    //the given token is for kebab3
    PvRepository pvRepo;
    pvRepo.getList("6f72830134afcffe5fefba61c3216931");
    pvRepo.getChats("6f72830134afcffe5fefba61c3216931","kebab4","20230701121345");
    pvRepo.getChats("6f72830134afcffe5fefba61c3216931","kebab2","20230630170702");
    pvRepo.writeMessages();
    pvRepo.sendMessage("6f72830134afcffe5fefba61c3216931","kebab4","alan ferestadam");
    pvRepo.readMessages();
    const std::vector<std::unique_ptr<DTO>>& pvList = pvRepo.Repository::getList();
    for (const auto& pvPtr : pvList) {
        qDebug() << "Pv Name: " << pvPtr->getName();
        qDebug() << "Messages: ";
        const QMultiMap<QString, QPair<QString, QString>>& messages = pvPtr->getMessages();
    }
    //pvRepo.removeDir();



    MainWindow w(groupList , pvList , channelList , groupRepo , channelRepo , pvRepo );
    w.show();
    return app.exec();


return app.exec();
}

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QThread>
#include "mainwindow.h"
#include "httphandler.h"
#include "urlmaker.h"
#include "client.h"
#include "exceptionhandler.h"
#include "grouprepository.h"
#include "channel.h"
#include "channelrepository.h"
#include "pvrepository.h"
#include "pv.h"
#include "channel.h"
#include "channelrepository.h"
#include "repository.h"



int main(int argc, char *argv[]){
QApplication app(argc, argv);
Client cl;


//test pv
//the tester is kebab2
//the other user is kebab3
Pv p("kebab3");
PvRepository pr;
//pr.sendmessagePv("kebab3","salam da",cl);
pr.getPvlist(cl);
pr.getPvchats(cl,"kebab3","");
QList<Pv> List = pr.getPv_list();
pr.WritePvsmessages();
pr.display();
//pr.ReadPvsmessages();
for (const Pv& p1 : List) {
    qDebug() << "Pv Name: " << p1.getPvname();
    qDebug() << "Messages: ";
    const QMultiMap<QString, QPair<QString, QString>>& messages = p1.getPvmessages();
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
}
pvRepo.removeDir();

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
//pr.RemovePvsDir();




//test group
Group g("","lmao");
GroupRepository gr;
gr.joinGroup(cl,"lmao");
gr.joinGroup(cl,"new");
gr.joinGroup(cl,"nmdvaghean");
//gr.sendmessageGroup("lmao","salam da",cl);
gr.getGrouplist(cl);
gr.getGroupchats(cl,"lmao","");
gr.getGroupchats(cl,"new","");
gr.getGroupchats(cl,"nmdvaghean","");
QList<Group> ListG = gr.getGroup_list();
gr.WriteGroupsmessages();
gr.display();
//gr.ReadGroupsmessages();
for (const Group& g1 : ListG) {
    qDebug() << "group Name: " << g1.getGroupname();
    qDebug() << "Messages: ";
    const QMultiMap<QString, QPair<QString, QString>>& messages = g1.getGroupmessages();
    for (auto it = messages.constBegin(); it != messages.constEnd(); ++it) {
        qDebug() << "Date: " << it.key() << ", src: " << it.value().first << ", message: " << it.value().second;
    }
}
//gr.RemoveGroupsDir();



//test channel
Channel c("lmao");
ChannelRepository cr;
//cr.joinChannel(cl,"lmao");
//cr.joinChannel(cl,"new");
//cr.joinChannel(cl,"nmdvaghean");
//cr.createChannel(cl,"lmaochannel");
//cr.createChannel(cl,"newchannel");
//cr.createChannel(cl,"nmdvagheanchannel");
//cr.sendmessageChannel("lmaochannel","salam da1",cl);
//cr.sendmessageChannel("lmaochannel","salam da2",cl);
//cr.sendmessageChannel("lmaochannel","salam da3",cl);
//cr.sendmessageChannel("newchannel","salam da1",cl);
//cr.sendmessageChannel("newchannel","salam da2",cl);
//cr.sendmessageChannel("lmaochannel","salam da3",cl);
//cr.sendmessageChannel("nmdvagheanchannel","salam da4",cl);
cr.getChannellist(cl);
cr.getChannelchats(cl,"lmaochannel","");
cr.getChannelchats(cl,"newchannel","");
cr.getChannelchats(cl,"nmdvagheanchannel","");
QList<Channel> ListC = cr.getChannel_list();
cr.WriteChannelsmessages();
cr.display();
//cr.ReadChannelsmessages();
for (const Channel& c1 : ListC) {
    qDebug() << "Channel Name: " << c1.getChannelname();
    qDebug() << "Messages: ";
    const QMultiMap<QString, QPair<QString, QString>>& messages = c1.getChannelmessages();
    for (auto it = messages.constBegin(); it != messages.constEnd(); ++it) {
        qDebug() << "Date: " << it.key() << ", src: " << it.value().first << ", message: " << it.value().second;
    }
}
//gr.RemoveGroupsDir();




//GroupRepository gr;
//gr.RemoveGroupsDir();
//Client cl("kebab","6kebab","kebab","kebab");
//cl.Login();
//cl.Logout();
//cl.WriteClient();
//HttpHandler http;
//Client cl("kebab11dsf11","1111sdfkebab","kebab","kebab");
//QPair<QJsonObject, bool> response = http.makeRequest("http://invalidurl.com");

//cl.Login();
//cl.RemoveClientDir();
//cl.ReadClient();
//QPair<QString , QString> response =cl.Login();
//GroupRepository groupRepo;
//groupRepo.getGrouplist(cl);
//groupRepo.getGroupchats(cl,"lmao","");
////groupRepo.getGroupchats(cl,"new","");
//groupRepo.WriteGroupsmessages();
////groupRepo.ReadGroupsmessages();
//QList<Group> groupList = groupRepo.getGroup_list();
//for (const Group& group : groupList) {
//    qDebug() << "Group Name: " << group.getGroupname();
//    qDebug() << "Messages: ";
//    const QMultiMap<QString, QPair<QString, QString>>& messages = group.getGroupmessages();
//    for (auto it = messages.constBegin(); it != messages.constEnd(); ++it) {
//        qDebug() << "Sender: " << it.key() << ", Text: " << it.value().first << ", Date: " << it.value().second;
//    }
//}
//cl.Logout();
//gr.createChannel(cl , "nmdvaghean9");
//QThread::msleep(20000);
//gr.joinChannel(cl,"nmdvaghean9");
//gr.sendmessageChannel("nmdvaghean9","asdasd",cl);
//gr.sendmessageChannel("nmdvaghean9","zcx",cl);
//gr.sendmessageChannel("nmdvaghean9","vcb",cl);
//gr.sendmessageChannel("nmdvaghean9","ZXtry",cl);
//gr.getChannellist(cl);
//gr.getChannelchats(cl,"nmdvaghean9","");
//QList<Channel> List=gr.getChannel_list();

//gr.WriteChannelsmessages();
//gr.ReadChannelsmessages();
//QList<Channel> groupList = gr.getChannel_list();
//for (const Channel& group : groupList) {
//    qDebug() << "Group Name: " << group.getChannelname();
//    qDebug() << "Messages: ";
//    const QMultiMap<QString, QPair<QString, QString>>& messages = group.getChannelmessages();
//    for (auto it = messages.constBegin(); it != messages.constEnd(); ++it) {
//        qDebug() << "Sender: " << it.key() << ", Text: " << it.value().first << ", Date: " << it.value().second;
//    }
//}
//gr.RemoveChannelsDir();
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
//    if (!response.second) {
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
//    Client newuser("kebab", "6kebab", "kebabist", "jooj");
//    newuser.Signup();
    MainWindow w(g , gr , c , cr , p , pr);
    w.show();
    return app.exec();


return app.exec();
}

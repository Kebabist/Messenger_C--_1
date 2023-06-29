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
//ChannelRepository gr;
//test pv
//the tester is kebab2
//the other user is kebab3
Client cl;
Pv p("kebab3");
PvRepository pr;
pr.sendmessagePv("kebab3","salam da",cl);
pr.getPvlist(cl);
pr.getPvchats(cl,"kebab3","");
QList<Pv> List = pr.getPv_list();
pr.WritePvsmessages();
pr.display();
pr.ReadPvsmessages();
for (const Pv& Pv : List) {
    qDebug() << "Channel Name: " << Pv.getPvname();
    qDebug() << "Messages: ";
    const QMultiMap<QString, QPair<QString, QString>>& messages = Pv.getPvmessages();
    for (auto it = messages.constBegin(); it != messages.constEnd(); ++it) {
        qDebug() << "Date: " << it.key() << ", src: " << it.value().first << ", message: " << it.value().second;
    }
}
pr.RemovePvsDir();

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
    return app.exec();
}


#ifndef CHANNELREPOSITORY_H
#define CHANNELREPOSITORY_H

#include <QWidget>
#include <QList>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDir>
#include <QFile>
#include <QByteArray>
#include <QStandardPaths>
#include "channel.h"
#include "httpHandler.h"
#include "urlmaker.h"
#include "client.h"

class ChannelRepository
{
public:
    ChannelRepository();
    ~ChannelRepository();

    void createChannel(Client &c , QString);
    void joinChannel(Client &c ,QString);
    void getChannellist(Client &c);
    void getChannelchats(Client &c , QString dst , QString date);
    void sendmessageChannel(QString desiredChannel , QString text , Client &c);
    void display();
    void RemoveChannelsDir();
    void WriteChannelsmessages();
    void ReadChannelsmessages();

    //setter function
    void setChannelsList(const Channel& newChannel );

    //getter function
    const QList<Channel>& getChannel_list() const;


private:
    HttpHandler http;
    urlmaker urlMaker;
    QList<Channel> Channels_list;
};

#endif // CHANNELREPOSITORY_H

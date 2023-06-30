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
#include <vector>
#include "channel.h"
#include "httpHandler.h"
#include "urlmaker.h"
#include "client.h"

class ChannelRepository
{
public:
    ChannelRepository();
    ~ChannelRepository();

    void createChannel(QString token, QString ChannelName);
    void joinChannel(QString token ,QString ChannelName);
    void getChannellist(QString token);
    void sendmessageChannel(QString token, QString ChannelName , QString message);
    const QString findLatestdate(QString ChannelName) const;
    void getChannelchats(QString token , QString ChannelName , QString date);
    void RemoveChannelsDir();
    void WriteChannelsmessages();
    void ReadChannelsmessages();
    void display();

    //setter function
    void setChannelsList(const std::unique_ptr<Channel> newChannel);

    //getter function
    const std::vector<std::unique_ptr<Channel>>& getChannel_list() const;

private:
    HttpHandler http;
    urlmaker urlMaker;
    std::vector<std::unique_ptr<Channel>> Channels_list;
};

#endif // CHANNELREPOSITORY_H

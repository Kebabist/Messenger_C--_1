#ifndef CHANNELREPOSITORY_H
#define CHANNELREPOSITORY_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QDir>
#include <QFile>
#include <QByteArray>
#include <QStandardPaths>
#include <vector>
#include "channel.h"
#include "repository.h"

class ChannelRepository : public Repository
{
public:
    ChannelRepository();
    ~ChannelRepository();

    void create(QString token, QString name) override;
    void join(QString token, QString name) override;
    void getList(QString token) override;
    void sendMessage(QString token, QString name, QString message) override;
    const QString findLatestDate(QString name) override;
    void getChats(QString token, QString name, QString date) override;
    void removeDir() override;
    void writeMessages() override;
    void readMessages() override;
    void display() override;
};

#endif // CHANNELREPOSITORY_H

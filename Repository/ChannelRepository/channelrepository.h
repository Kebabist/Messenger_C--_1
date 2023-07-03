#ifndef CHANNELREPOSITORY_H
#define CHANNELREPOSITORY_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QDir>
#include <QFile>
#include <QByteArray>
#include <QStandardPaths>
#include <vector>
#include "Repository/Repository/repository.h"
#include "DTO/Channel/channel.h"

class ChannelRepository : public Repository
{
public:
    ChannelRepository();
    ChannelRepository(const ChannelRepository& other);
    ~ChannelRepository();

    QString join(QString token, QString name) override;
    QString create(QString token, QString name) override;
    void getList(QString token) override;
    QString sendMessage(QString token, QString name, QString message) override;
    const QString findLatestDate(QString name) override;
    void getChats(QString token, QString name, QString date= "") override;
    void removeDir() override;
    void writeMessages() override;
    void readMessages() override;
    void display() override;
};

#endif // CHANNELREPOSITORY_H

#ifndef GROUPREPOSITORY_H
#define GROUPREPOSITORY_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QDir>
#include <QFile>
#include <QByteArray>
#include <QStandardPaths>
#include <vector>
#include"group.h"
#include "repository.h"

class GroupRepository : public Repository
{
public:
    GroupRepository();
    ~GroupRepository();

    void create(QString token, QString name) override;
    void join(QString token, QString name) override;
    void getList(QString token) override;
    void sendMessage(QString token, QString name, QString message) override;
    const QString findLatestDate(QString name) const override;
    void getChats(QString token, QString name, QString date) override;
    void removeDir() override;
    void writeMessages() override;
    void readMessages() override;
    void display() override;
};

#endif // GROUPREPOSITORY_H

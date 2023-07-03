#ifndef GROUPREPOSITORY_H
#define GROUPREPOSITORY_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QDir>
#include <QFile>
#include <QByteArray>
#include <QStandardPaths>
#include <vector>
#include "Repository/Repository/repository.h"
#include "DTO/Group/group.h"

class GroupRepository : public Repository
{
public:
    GroupRepository();
    GroupRepository(const GroupRepository& other);
    ~GroupRepository();

    QString create(QString token, QString name) override;
    QString join(QString token, QString name) override;
    void getList(QString token) override;
    QString sendMessage(QString token, QString name, QString message) override;
    const QString findLatestDate(QString name) override;
    void getChats(QString token, QString name, QString date= "") override;
    void removeDir() override;
    void writeMessages() override;
    void readMessages() override;
    void display() override;
};

#endif // GROUPREPOSITORY_H

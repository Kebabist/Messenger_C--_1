#ifndef GROUPREPOSITORY_H
#define GROUPREPOSITORY_H

#include <QWidget>
#include <QList>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDir>
#include <QFile>
#include <QByteArray>
#include <QStandardPaths>
#include"group.h"
#include "httpHandler.h"
#include "urlmaker.h"
#include "client.h"

class GroupRepository : public QWidget
{
    Q_OBJECT

public:
    GroupRepository();
    ~GroupRepository();

    void createGroup(QString token, QString groupName);
    void joinGroup(QString token ,QString groupName);
    void getGrouplist(QString token);
    void sendmessageGroup(QString token, QString groupName , QString message);
    const QString findLatestdate(QString groupName) const;
    void getGroupchats(QString token , QString groupName , QString date);
    void RemoveGroupsDir();
    void WriteGroupsmessages();
    void ReadGroupsmessages();
    void display();

    //setter function
    void setGroupsList(const std::unique_ptr<Group> newgroup);

    //getter function
    const std::vector<std::unique_ptr<Group>>& getGroup_list() const;

private:
    HttpHandler http;
    urlmaker urlMaker;
    std::vector<std::unique_ptr<Group>> Groups_list;
};

#endif // GROUPREPOSITORY_H

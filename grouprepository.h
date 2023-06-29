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
//    explicit GroupRepository(QWidget *parent = nullptr);
    GroupRepository();
    ~GroupRepository();

    void createGroup(Client &c , QString);
    void joinGroup(Client &c ,QString);
    void getGrouplist(Client &c);
    void getGroupchats(Client &c , QString dst , QString date);
    void sendmessageGroup(QString desiredgroup , QString text , Client &c);
    void display();
    void RemoveGroupsDir();

    //setter function
    void setGroupsList(const Group& newgroup );

    //getter function
    const QList<Group>& getGrouplist() const;


private:
    HttpHandler http;
    urlmaker urlMaker;
    QList<Group> Groups_list;
};

#endif // GROUPREPOSITORY_H

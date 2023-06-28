#ifndef GROUPREPOSITORY_H
#define GROUPREPOSITORY_H

#include <QWidget>
#include <QList>
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

    void create(Client &c);
    Group read(int id) const;
    void update(const Group& group);
    void remove(int id);
    void getGroupslist(QString token, QString dst, QString time);

    //getter function
     QList<Group> getAllGroups() const;

private:
    HttpHandler http;
    urlmaker urlMaker;
    QList<Group> Groups_list;
};

#endif // GROUPREPOSITORY_H

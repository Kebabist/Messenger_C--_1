#ifndef GROUPREPOSITORY_H
#define GROUPREPOSITORY_H

#include <QWidget>
#include <QList>
#include"group.h"
#include "httpHandler.h"
#include "urlmaker.h"

class GroupRepository : public QWidget
{
    Q_OBJECT

public:
//    explicit GroupRepository(QWidget *parent = nullptr);
    GroupRepository();
    ~GroupRepository();

    void create(const Group& group);
    Group read(int id) const;
    void update(const Group& group);
    void remove(int id);
    void getGroupslist(QString token, QString dst, QString time);

    //getter function
     QList<Group> getAllGroups() const;
signals:
    void groupsChanged(const QList<Group>& groups);

private slots:
    void onGroupsReceived(const QByteArray& data);

private:
    HttpHandler http;
    urlmaker urlMaker;
    QList<Group> Groups_list;
};

#endif // GROUPREPOSITORY_H

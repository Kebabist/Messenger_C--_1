#ifndef GROUP_H
#define GROUP_H

#include <QWidget>
#include <QString>
#include <qmap.h>

//Group class that holds necessary Group data
class Group : public QWidget
{
    Q_OBJECT

public:

    Group();
    Group(QString name);
    Group(const Group& other);
    Group& operator=(const Group& other);
    ~Group();

    //getter
    QString getGroupname() const;
    const QMultiMap<QString, QPair<QString, QString>> &getGroupmessages() const;

    //setter
    void setGroupmessages(QString src , QString  message , QString date);

private:
    QString Group_name;
    QMultiMap<QString, QPair<QString, QString>> Group_messages;
};



#endif // GROUP_H

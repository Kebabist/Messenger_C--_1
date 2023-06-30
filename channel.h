#ifndef CHANNEL_H
#define CHANNEL_H

#include <QString>
#include <qmap.h>

class Channel
{    
public:

    Channel();
    Channel(QString name);
    Channel(const Channel& other);
    Channel& operator=(const Channel& other);
    ~Channel();

    //getter
    QString getChannelname() const;
    const QMultiMap<QString, QPair<QString, QString>> &getChannelmessages() const;

    //setter
    void setChannelmessages(QString src , QString  message , QString date);

private:
    QString Channel_name;
    QMultiMap<QString, QPair<QString, QString>> Channel_messages;
};

#endif // CHANNEL_H


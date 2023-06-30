#ifndef CHANNEL_H
#define CHANNEL_H

#include <QString>
#include <qmap.h>

class Channel
{
public:
    Channel();
    Channel(const QString& name);
    Channel(const Channel& other);
    Channel& operator=(const Channel& other);
    ~Channel();

    //getter
    QString getChanneltitle() const;
    QString getChannelname() const;
    const QMultiMap<QString, QPair<QString, QString>> &getChannelmessages() const;

    //overloading
    bool operator==(const Channel& other) const;


    //setter
    void setChannelmessages(QString  , QString   , QString );

private:
    QString Channel_name;
    QMultiMap<QString, QPair<QString, QString>> Channel_messages;
};

#endif // CHANNEL_H

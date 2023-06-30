#include "channel.h"

//default constructor
Channel::Channel()
{}

//Channel class Constructor
Channel::Channel(const QString& name)
    : Channel_name(name)
{}

//copy constructor
Channel::Channel(const Channel& other)
    : Channel_name(other.Channel_name), Channel_messages(other.Channel_messages)
{}

//setter
void Channel::setChannelmessages(QString src , QString  message , QString date){
    Channel_messages.insert(date, QPair<QString, QString>(src, message));
}


//overloading
bool Channel::operator==(const Channel& other) const {
    return Channel_name == other.Channel_name;
}

//copy assignment operator
Channel& Channel::operator=(const Channel& other)
{
    if (this != &other) {
        Channel_name = other.Channel_name;
        Channel_messages = other.Channel_messages;
    }
    return *this;
}

Channel::~Channel()
{}

//getter functions
QString Channel::getChannelname() const{
    return Channel_name;
}

const QMultiMap<QString, QPair<QString, QString>>& Channel::getChannelmessages() const  {
    return Channel_messages;
}

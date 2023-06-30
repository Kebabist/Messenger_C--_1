#include "group.h"
//#include "Ui_group.h"

//default constructor
Group::Group()
{}

//Group class Constructor
Group::Group(QString name)
    : Group_name(name)
{}

//copy constructor
Group::Group(const Group& other)
    : Group_name(other.Group_name), Group_messages(other.Group_messages)
{}

//setter
void Group::setGroupmessages(QString src , QString  message , QString date){
    Group_messages.insert(date, QPair<QString, QString>(src, message));
}

//copy assignment operator
Group& Group::operator=(const Group& other)
{
    if (this != &other) { 
        Group_name = other.Group_name;
        Group_messages = other.Group_messages;
    }
    return *this;
}

Group::~Group()
{}

//getter functions
QString Group::getGroupname() const{
    return Group_name;
}

const QMultiMap<QString, QPair<QString, QString>>& Group::getGroupmessages() const  {
    return Group_messages;
}

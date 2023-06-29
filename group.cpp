#include "group.h"
//#include "Ui_group.h"

//Group::Group(QWidget *parent)
//    : QWidget(parent), Group_id(0), Group_name(""), Group_messages(QMap<QString, QString>()), ui(new Ui::Group)
//{
//    ui->setupUi(this);
//}

//Group::~Group()
//{
//    delete ui;
//}
//default constructor
Group::Group()
{}

//Group class Constructor
Group::Group(QString title, const QString& name)
    : Group_title(title), Group_name(name)
{}

//copy constructor
Group::Group(const Group& other)
    : Group_title(other.Group_title), Group_name(other.Group_name), Group_messages(other.Group_messages)
{}

//setter
void Group::setGroupmessages(QString date , QString  src , QString message){
    Group_messages.insert(date, QPair<QString, QString>(src, message));
}


//overloading
bool Group::operator==(const Group& other) const {
    return Group_name == other.Group_name;
}

//copy assignment operator
Group& Group::operator=(const Group& other)
{
    if (this != &other) {
        Group_title = other.Group_title;
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

QString Group::getGrouptitle() const{
    return Group_title;
}

const QMultiMap<QString, QPair<QString, QString>>& Group::getGroupmessages() const  {
    return Group_messages;
}

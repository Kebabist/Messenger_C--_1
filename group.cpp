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

//Group class Constructor
Group::Group(QString title, const QString& name, const QMap<QString, QString>& messages)
    : Group_title(title), Group_name(name), Group_messages(messages)
{}

//copy constructor
Group::Group(const Group& other)
    : Group_title(other.Group_title), Group_name(other.Group_name), Group_messages(other.Group_messages)
{}

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
QMap<QString, QString> Group::getGroupmessages() const{
    return Group_messages;
}

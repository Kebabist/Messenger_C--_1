#include "group.h"
#include "Ui_group.h"

Group::Group(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Group)
{
    ui->setupUi(this);
}

Group::~Group()
{
    delete ui;
}

//default Group class constructor
Group::Group() : Group_id(0)
{}

//Group class Constructor
Group::Group(int id, const QString& name, const QMap<QString, QString>& messages)
    : Group_id(id), Group_name(name), Group_messages(messages)
{}

//getter functions
QString Group::getGroupname() const{
    return Group_name;
}
int Group::getGroupid() const{
    return Group_id;
}
QMap<QString, QString> Group::getGroupmessages() const{
    return Group_messages;
}

#include "grouprepository.h"
//#include "Ui_grouprepository.h"

//GroupRepository::GroupRepository(QWidget *parent) :
//    QWidget(parent),
//    ui(new Ui::GroupRepository)
//{
//    ui->setupUi(this);
//}

//GroupRepository default constructor
GroupRepository::GroupRepository(){
    connect(&http, &HttpHandler::requestFinished, this, &GroupRepository::onGroupsReceived);
}

void GroupRepository::create(const Group& group)
{
    Groups_list.push_back(group);
}

//destructor
GroupRepository::~GroupRepository()
{}

//reads the group list and finds and returns the specified group
Group GroupRepository::read(QString token) const
{
    for (const Group& group : Groups_list) {
        if (group.getGroupid() == token) {
            return group;
        }
    }
    return Group();
}

//Updates a Group data in Groups_list
void GroupRepository::update(const Group& group)
{
    for (Group& g : Groups_list) {
        if (g.getGroupid() == group.getGroupid()) {
            g = group;
            break;
        }
    }
}

//removes a group from the Groups_list
void GroupRepository::remove(int id)
{
    auto iter = std::remove_if(Groups_list.begin(), Groups_list.end(), [id](const Group& group) {
        return group.getGroupid() == id;
    });
    Groups_list.erase(iter, Groups_list.end());
}

//reads the Whole Groups_list and returns it
QList<Group> GroupRepository::getAllGroups() const
{
    return Groups_list;
}

//
void GroupRepository::getGroupslist(QString token, QString dst, QString time){
    m_urlMaker = urlmaker("groups", QString("userId=%1").arg(userId));
    QString url = m_urlMaker.generate();
    QPair<QJsonObject, bool> result = m_httpHandler.makeRequest(url);
    if (result.second) {
        QJsonArray jsonArray = result.first.array();

        QList<Group> groups;
        for (const QJsonValue& value : jsonArray) {
            QJsonObject jsonObject = value.toObject();
            int id = jsonObject.value("id").toInt();
            QString name = jsonObject.value("name").toString();
            QList<QString> messages;

            // Parse messages array
            QJsonArray messagesArray = jsonObject.value("messages").toArray();
            for (const QJsonValue& messageValue : messagesArray) {
                QString message = messageValue.toString();
                messages.append(message);
            }

            Group group(id, name, messages);
            groups.append(group);
        }

        Groups_list = groups;
        emit groupsChanged(Groups_list);
    }
}

//void GroupDTO::getGroups(QString token, QString dst, QString time)
//{
//    QString arguments = "username=sara&password=1234&firstname=sara&lastname=baradaran";
//    //    urlmaker newurl("signup" , "token" , arguments);
//    //    const QString url = newurl.generate();
//    QUrl url("http://example.com/groups?userId=" + QString::number(userId));
//    QByteArray data = http.get(url);
//    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
//    QJsonArray jsonArray = jsonDoc.array();

//    for (const QJsonValue& value : jsonArray) {
//        QJsonObject jsonObject = value.toObject();
//        int id = jsonObject.value("id").toInt();
//        QString name = jsonObject.value("name").toString();
//        QMap<QString, QString> messages;

//        // Parse messages array
//        QJsonArray messagesArray = jsonObject.value("messages").toArray();
//        for (const QJsonValue& messageValue : messagesArray) {
//            QJsonObject messageObject = messageValue.toObject();
//            QString message = messageObject.value("message").toString();
//            QString timestamp = messageObject.value("timestamp").toString();
//            messages[message] = timestamp;
//        }

//        Group group(id, name, messages);
//        groupRepository.create(group);
//    }

//    QList<Group> groups = groupRepository.getAllGroups();
//    emit groupsReceived(groups);
//}

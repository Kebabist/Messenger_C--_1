#include "grouprepository.h"
#include "Ui_grouprepository.h"

GroupRepository::GroupRepository(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupRepository)
{
    ui->setupUi(this);
}

GroupRepository::~GroupRepository()
{
    delete ui;
}

//GroupRepository default constructor
GroupRepository::GroupRepository()
{}

void GroupRepository::create(const Group& group)
{
    Groups_list.push_back(group);
}

//reads the group list and finds and returns the specified group
Group GroupRepository::read(int id) const
{
    for (const Group& group : Groups_list) {
        if (group.getGroupid() == id) {
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

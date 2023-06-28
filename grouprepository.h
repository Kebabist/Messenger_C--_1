#ifndef GROUPREPOSITORY_H
#define GROUPREPOSITORY_H

#include <QWidget>
#include <QList>
#include"group.h"

namespace Ui {
class GroupRepository;
}

class GroupRepository : public QWidget
{
    Q_OBJECT

public:
    explicit GroupRepository(QWidget *parent = nullptr);
    GroupRepository();
    ~GroupRepository();

    void create(const Group& group);
    Group read(int id) const;
    void update(const Group& group);
    void remove(int id);

    //getter function
     QList<Group> getAllGroups() const;

private:
    QList<Group> Groups_list;
    Ui::GroupRepository *ui;
};

#endif // GROUPREPOSITORY_H

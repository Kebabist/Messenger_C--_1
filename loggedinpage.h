#ifndef LOGGEDINPAGE_H
#define LOGGEDINPAGE_H

#include <QWidget>
#include "client.h"
#include <qlistwidget.h>
#include "group.h"
#include "grouprepository.h"

namespace Ui {
class loggedinpage;
}

class loggedinpage : public QWidget
{
    Q_OBJECT

public:
    explicit loggedinpage(Group & , GroupRepository & ,Client &client , QWidget *parent = nullptr);
    void addtopage(const QList<Group>&);
    ~loggedinpage();

private slots:
    void on_toggleview_clicked(bool checked);
    void handleListItemClicked(QListWidgetItem* item);
    void on_logoutbutton_clicked();

signals:
    //emit when the button is clicked
    void logoutbuttonclicked();

private:
    Ui::loggedinpage *ui;
    Client cl;
    Group group;
    GroupRepository grouprepo;
    QMultiMap<QString, QPair<QString , QString>> group_messages;
};

#endif // LOGGEDINPAGE_H

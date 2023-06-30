#ifndef LOGGEDINPAGE_H
#define LOGGEDINPAGE_H

#include <QWidget>
#include "client.h"
#include <qlistwidget.h>
#include "group.h"
#include "grouprepository.h"
#include "channel.h"
#include "channelrepository.h"
#include "pv.h"
#include "pvrepository.h"

namespace Ui {
class loggedinpage;
}

class loggedinpage : public QWidget
{
    Q_OBJECT

public:
    explicit loggedinpage(Group &g , GroupRepository &gr , Channel &c , ChannelRepository &cr , Pv &p , PvRepository &pr,Client &client , QWidget *parent = nullptr);
    void addtopage(const QList<Group> &groupList);
    void addtopage(const QList<Channel> &channelList);
    void addtopage(const QList<Pv> &pvList);
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
    Channel channel;
    ChannelRepository channelrepo;
    Pv pv;
    PvRepository pvrepo;
    QMultiMap<QString, QPair<QString , QString>> group_messages;
    QMultiMap<QString, QPair<QString , QString>> channel_messages;
    QMultiMap<QString, QPair<QString , QString>> pv_messages;
};

#endif // LOGGEDINPAGE_H

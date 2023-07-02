#ifndef LOGGEDINPAGE_H
#define LOGGEDINPAGE_H

#include <QWidget>
#include "client.h"
#include <qlistwidget.h>
#include <QtConcurrent/qtconcurrentrun.h>
#include <QThreadPool>
#include <QTimer>
#include "grouprepository.h"
#include "channelrepository.h"
#include "pvrepository.h"

namespace Ui {
class loggedinpage;
}

class loggedinpage : public QWidget
{
    Q_OBJECT

public:
    explicit loggedinpage(Client& client,
                          GroupRepository& groupRepo,
                          ChannelRepository& channelRepo,
                          PvRepository& pvRepo, QWidget *parent = nullptr);
    void addtopage(const std::vector<std::unique_ptr<DTO>>& List);
    ~loggedinpage();

private slots:
    void on_toggleview_clicked(bool checked);
    void handleListItemClicked(QListWidgetItem* item);
    void updateSelectedChat();
    void on_logoutbutton_clicked();
    void on_joingroupbtton_clicked();
    void on_creategroupbutton_clicked();
    void on_sendmessagebutton_clicked();

    void on_joinchannelbutton_clicked();

    void on_createchannelbutton_clicked();

    void on_newchatbutton_clicked();

signals:
    //emit when the button is clicked
    void logoutbuttonclicked();

private:
    void updatelists();
    void updateGroupMessages();
    void updateChannelMessages();
    void updatePvMessages();
    Client& client;
    Ui::loggedinpage *ui;
    QTimer *updateTimer;
    QPair<QString , QString> selected; //first one is the type //second one is the name //Like : <group , groupName>
    GroupRepository& groupRepo;
    ChannelRepository& channelRepo;
    PvRepository& pvRepo;
    QMultiMap<QString, QPair<QString , QString>> group_messages;
    QMultiMap<QString, QPair<QString , QString>> channel_messages;
    QMultiMap<QString, QPair<QString , QString>> pv_messages;
    QThread *messageThread;
};

#endif // LOGGEDINPAGE_H

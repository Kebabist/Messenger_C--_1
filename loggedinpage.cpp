#include "loggedinpage.h"
#include "mainwindow.h"
#include "exceptionhandler.h"
#include "ui_loggedinpage.h"
#include <qmessagebox.h>


loggedinpage::loggedinpage(Group &g , GroupRepository &gr , Channel &c , ChannelRepository &cr , Pv &p , PvRepository &pr, Client& client, QWidget* parent) :
    QWidget(parent),
    ui(new Ui::loggedinpage),
    cl(client),
    group(g),
    grouprepo(gr),
    channel(c),
    channelrepo(cr),
    pv(p),
    pvrepo(pr)
{
    //parent->hide();
    ui->setupUi(this);
    //connect(ui->toggleview, SIGNAL(clicked(bool)), this, SLOT(onToggleviewClicked(bool)));
    connect(ui->allchats, &QListWidget::itemClicked, this, &loggedinpage::handleListItemClicked);
    ui->dockWidget->setTitleBarWidget(ui->widget_3);
    QList<Group> groups = grouprepo.getGroup_list();
    addtopage(groups); // Add groups to the list widget
    QList<Channel> channels = channelrepo.getChannel_list();
    addtopage(channels); // Add channels to the list widget
    QList<Pv> pvs = pvrepo.getPv_list();
    addtopage(pvs); // Add pvs to the list widget
}

loggedinpage::~loggedinpage()
{
    delete ui;
}

void loggedinpage::on_toggleview_clicked(bool checked)
{
    // Get the current size of the button
    QSize currentSize = ui->toggleview->size();

    // Set the new size of the button
    if (!checked){
        QSize newSize(currentSize.width() * 0.1, currentSize.height() * 0.1);
        ui->toggleview->resize(newSize);
    } else {
        QSize newSize(currentSize.width() / 0.1, currentSize.height() / 0.1);
        ui->toggleview->resize(newSize);
    }

    ui->dockWidget->setVisible(!checked);
}




void loggedinpage::handleListItemClicked(QListWidgetItem* item)
{
    QString text = item->text();



    QString substrgr = "group: ";
    QString substrch = "channel: ";
    QString substrpv = "pv: ";
    QString groupName = "";
    QString channelName = "";
    QString pvName = "";
    // Find the index of the group in the string
    int index = text.indexOf(substrgr);

    // If the substring is found, remove it from the string
    if (index != -1) {
        text.remove(index, substrgr.length());
        groupName = text;
    }else{
        index = text.indexOf(substrch);
        if (index != -1) {
            text.remove(index, substrch.length());
            channelName = text;
        }else {
            index = text.indexOf(substrpv);
            if (index != -1) {
                text.remove(index, substrpv.length());
                pvName = text;
            }
        }
    }

    if (groupName != ""){
        // Find the group object from the group_list that matches the clicked group name
        Group group;
        for (auto& g : grouprepo.getGroup_list()) {
            if (g.getGroupname() == groupName) {
                // Get the group messages from the found group object
                QMultiMap<QString, QPair<QString , QString>> groupMessages = g.getGroupmessages();
                // Show the group messages in a text widget
                ui->messages->clear();
                for (QMultiMap<QString, QPair<QString , QString>>::Iterator it =groupMessages.begin() ; it != groupMessages.end(); ++it) {
                    QString sender = it.value().first;
                    QString text = it.value().second;
                    ui->messages->appendPlainText(sender + ": " + text);
                }
                break;
            }
        }
    }else if (channelName != ""){
        // Find the channel object from the channel_list that matches the clicked channel name
        for (auto& c : channelrepo.getChannel_list()) {
            if (c.getChannelname() == channelName) {
                // Get the channel messages from the found channel object
                QMultiMap<QString, QPair<QString , QString>> channelMessages = c.getChannelmessages();

                // Show the channel messages in a text widget
                ui->messages->clear();
                for (QMultiMap<QString, QPair<QString , QString>>::Iterator it =channelMessages.begin() ; it != channelMessages.end(); ++it) {
                    QString sender = it.value().first;
                    QString text = it.value().second;
                    ui->messages->appendPlainText(sender + ": " + text);
                }
                break;
            }
        }
    }else if (pvName != ""){
        // Find the PV object from the PV_list that matches the clicked PV name
        for (auto& p : pvrepo.getPv_list()) {
            if (p.getPvname() == pvName) {
                // Get the pv messages from the found pv object
                QMultiMap<QString, QPair<QString , QString>> pvMessages = p.getPvmessages();

                // Show the pv messages in a text widget
                ui->messages->clear();
                for (QMultiMap<QString, QPair<QString , QString>>::Iterator it =pvMessages.begin() ; it != pvMessages.end(); ++it) {
                    QString sender = it.value().first;
                    QString text = it.value().second;
                    ui->messages->appendPlainText(sender + ": " + text);
                }
                break;
            }
        }
    }

}

void loggedinpage::on_logoutbutton_clicked()
{
    try {
        QPair<QString , QString> response = cl.Logout(); // Pass the correct password parameter
        QMessageBox::information(this, "Information", response.second);
        emit logoutbuttonclicked();
    }catch (const ExceptionHandler &e) {
        QMessageBox::critical(this, "Error", e.message());
    }
}

//add to page
void loggedinpage::addtopage(const QList<Group>& groupList){
    for (const auto& groupName : groupList){
        QListWidgetItem* item = new QListWidgetItem("group: " +groupName.getGroupname());
        ui->allchats->addItem(item);
    }
}

//add to page overloading
void loggedinpage::addtopage(const QList<Channel>& channelList){
    for (const auto& channelName : channelList){
        QListWidgetItem* item = new QListWidgetItem("channel: "+channelName.getChannelname());
        ui->allchats->addItem(item);
    }
}
void loggedinpage::addtopage(const QList<Pv>& pvList){
    for (const auto& pvName : pvList){
        QListWidgetItem* item = new QListWidgetItem("pv: " + pvName.getPvname());
        ui->allchats->addItem(item);
    }
}






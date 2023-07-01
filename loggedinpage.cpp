#include "loggedinpage.h"
#include "mainwindow.h"
#include "exceptionhandler.h"
#include <QVector>
#include "ui_loggedinpage.h"
#include <QInputDialog>
#include <qmessagebox.h>


loggedinpage::loggedinpage(const std::vector<std::unique_ptr<DTO>>& passedgroupList,
                           const std::vector<std::unique_ptr<DTO>>& passedpvList,
                           const std::vector<std::unique_ptr<DTO>>& passedchannelList, Client& client, QWidget* parent) :
    QWidget(parent),
    ui(new Ui::loggedinpage),
    cl(client),
    pvList(passedpvList),
    groupList(passedgroupList),
    channelList(passedchannelList)
{
    //parent->hide();
    ui->setupUi(this);
    //connect(ui->toggleview, SIGNAL(clicked(bool)), this, SLOT(onToggleviewClicked(bool)));
    connect(ui->allchats, &QListWidget::itemClicked, this, &loggedinpage::handleListItemClicked);
    ui->dockWidget->setTitleBarWidget(ui->widget_3);
    addtopage(groupList); // Add group chats to the list widget
    addtopage(channelList); // Add channel chats to the list widget
    addtopage(pvList); // Add pv chats to the list widget
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



    QString substrgr = "G: ";
    QString substrch = "C: ";
    QString substrpv = "P: ";
    QString groupName = "";
    QString channelName = "";
    QString pvName = "";
    // Find the index of the group in the string
    int index = text.indexOf(substrgr);

    // If the substring is found, remove it from the string
    if (index != -1) {
        text.remove(index, substrgr.length());
        groupName = text;
        selected = qMakePair("group" , groupName);
    }else{
        index = text.indexOf(substrch);
        if (index != -1) {
            text.remove(index, substrch.length());
            channelName = text;
            selected = qMakePair("channel" , channelName);
        }else {
            index = text.indexOf(substrpv);
            if (index != -1) {
                text.remove(index, substrpv.length());
                pvName = text;
                selected = qMakePair("pv" , pvName);
            }
        }
    }

    if (groupName != ""){
        // Find the group object from the group_list that matches the clicked group name
        for (auto& g : groupList) {
            if (g->getName() == groupName) {
                // Get the group messages from the found group object
                QMultiMap<QString, QPair<QString , QString>> groupMessages = g->getMessages();
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
        for (auto& c : channelList) {
            if (c->getName() == channelName) {
                // Get the channel messages from the found channel object
                QMultiMap<QString, QPair<QString , QString>> channelMessages = c->getMessages();

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
        for (auto& p : pvList) {
            if (p->getName() == pvName) {
                // Get the pv messages from the found pv object
                QMultiMap<QString, QPair<QString , QString>> pvMessages = p->getMessages();

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
void loggedinpage::addtopage(const std::vector<std::unique_ptr<DTO>>& List){
    for (const auto& item : List) {
        const auto& Name = item->getName();
        const auto& Title = item->getTitle();
        QListWidgetItem* newItem = new QListWidgetItem(Title + ": " + Name);
        ui->allchats->addItem(newItem);
    }
}


void loggedinpage::on_joingroupbtton_clicked()
{
    GroupRepository grouprepo;
    bool ok;
    QString inputText = QInputDialog::getText(this, "Input Dialog", "Enter input:", QLineEdit::Normal, "", &ok);
    if (ok && !inputText.isEmpty()) {
        grouprepo.join("41c0089068b863e6a14ccc5d6dcda514" , inputText);
        //handle if join was successfull
        QMessageBox::information(this , "Information" , "joined the group successfully " + inputText);
    }
    //make an updater function then call it here to update the list and then call the addtopage() function on the new list;
}


void loggedinpage::on_creategroupbutton_clicked()
{
    GroupRepository grouprepo;
    bool ok;
    QString inputText = QInputDialog::getText(this, "Input Dialog", "Enter input:", QLineEdit::Normal, "", &ok);
    if (ok && !inputText.isEmpty()) {
        grouprepo.create("41c0089068b863e6a14ccc5d6dcda514" , inputText);
        //handle if join was successfull
        QMessageBox::information(this , "Information" , "group successfully made with name : " + inputText);
    }
    //make an updater function then call it here to update the list and then call the addtopage() function on the new list;
}



void loggedinpage::on_sendmessagebutton_clicked()
{
    if (selected.first == "group"){
        GroupRepository grouprepo;
        bool ok;
        QString inputText = QInputDialog::getText(this, "Input Dialog", "Enter input:", QLineEdit::Normal, "", &ok);
        if (ok && !inputText.isEmpty()) {
            grouprepo.create("41c0089068b863e6a14ccc5d6dcda514" , inputText);
            //handle if join was successfull
            QMessageBox::information(this , "Information" , "message successfully sent ");
        }
        //update the chatlist with the new message
        for (auto& g : groupList) {
            if (g->getName() == selected.second) {
                // Get the group messages from the found group object
                QMultiMap<QString, QPair<QString , QString>> groupMessages = g->getMessages();
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
    }
    //goes the same for pv and channel
}


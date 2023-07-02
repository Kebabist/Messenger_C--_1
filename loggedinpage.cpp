#include "loggedinpage.h"
#include "mainwindow.h"
#include "exceptionhandler.h"
#include <QVector>
#include "ui_loggedinpage.h"
#include <QInputDialog>
#include <qmessagebox.h>
#include <QTimer>

loggedinpage::loggedinpage(const std::vector<std::unique_ptr<DTO>>& passedgroupList,
                           const std::vector<std::unique_ptr<DTO>>& passedpvList,
                           const std::vector<std::unique_ptr<DTO>>& passedchannelList,
                           GroupRepository& groupRepo,
                           ChannelRepository& channelRepo,
                           PvRepository& pvRepo,
                           Client& client, QWidget* parent) :
    QWidget(parent),
    ui(new Ui::loggedinpage),
    cl(client),
    pvList(passedpvList),
    groupList(passedgroupList),
    channelList(passedchannelList),
    groupRepo(groupRepo),
    channelRepo(channelRepo),
    pvRepo(pvRepo)
{
    //parent->hide();
    ui->setupUi(this);
    //connect(ui->toggleview, SIGNAL(clicked(bool)), this, SLOT(onToggleviewClicked(bool)));
    connect(ui->allchats, &QListWidget::itemClicked, this, &loggedinpage::handleListItemClicked);
    ui->dockWidget->setTitleBarWidget(ui->widget_3);
    addtopage(groupList); // Add group chats to the list widget
    addtopage(channelList); // Add channel chats to the list widget
    addtopage(pvList); // Add pv chats to the list widget

    QThreadPool* threadPool = QThreadPool::globalInstance();
    threadPool->setMaxThreadCount(4);

    QtConcurrent::run(threadPool , [this]() {
        while (true) {
            updatelists();
            QThread::msleep(5000);
        }
    });

    // Execute the update group messages function asynchronously
    QtConcurrent::run(threadPool ,[this]() {
        while (true) {
            updateGroupMessages();
            QThread::msleep(5000);
        }
    });

    // Execute the update channel messages function asynchronously
    QtConcurrent::run(threadPool ,[this]() {
        while(true){
            updateChannelMessages();
            QThread::msleep(5000);
        }
    });

    // Execute the update private messages function asynchronously
    QtConcurrent::run(threadPool ,[this]() {
        while(true){
            updatePvMessages();
            QThread::msleep(5000);
        }
    });

}


void loggedinpage::updatelists(){
    groupRepo.getList("6f72830134afcffe5fefba61c3216931");;
    channelRepo.getList("6f72830134afcffe5fefba61c3216931");
    pvRepo.getList("6f72830134afcffe5fefba61c3216931");
    const std::vector<std::unique_ptr<DTO>>& groupList = groupRepo.Repository::getList();
    const std::vector<std::unique_ptr<DTO>>& channelList = channelRepo.Repository::getList();
    const std::vector<std::unique_ptr<DTO>>& pvList = pvRepo.Repository::getList();
    addtopage(groupList); // Add group chats to the list widget
    addtopage(channelList); // Add channel chats to the list widget
    addtopage(pvList); // Add pv chats to the list widget
}

void loggedinpage::updateGroupMessages(){
    for(auto &groupPtr : groupList){
        groupRepo.getChats("6f72830134afcffe5fefba61c3216931" , groupPtr->getName());
        QMultiMap<QString, QPair<QString , QString>> groupMessages = groupPtr->getMessages();
    }
}

void loggedinpage::updateChannelMessages(){
    for(auto &channelPtr : channelList){
        channelRepo.getChats("6f72830134afcffe5fefba61c3216931" , channelPtr->getName());
        QMultiMap<QString, QPair<QString , QString>> channelMessages = channelPtr->getMessages();
    }
}

void loggedinpage::updatePvMessages(){
    for(auto &p : pvList){
        pvRepo.getChats("6f72830134afcffe5fefba61c3216931" , p->getName());
        QMultiMap<QString, QPair<QString , QString>> pvMessages = p->getMessages();
    }
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
        // Find the group object from the grouplist that matches the clicked group name
        for (auto& g : groupList) {
            if (g->getName() == groupName) {
                // Get the group messages from the found group object
                QMultiMap<QString, QPair<QString , QString>> groupMessages = g->getMessages();
                // Show the group messages in a text widget
                ui->messages->clear();
                for (auto it =groupMessages.begin() ; it != groupMessages.end(); ++it) {
                    QString sender = it.value().first;
                    QString text = it.value().second;
                    ui->messages->appendPlainText(sender + ": " + text);
                }
                break;
            }
        }
    }else if (channelName != ""){
        // Find the channel object from the channellist that matches the clicked channel name
        for (auto& c : channelList) {
            if (c->getName() == channelName) {
                // Get the channel messages from the found channel object
                QMultiMap<QString, QPair<QString , QString>> channelMessages = c->getMessages();

                // Show the channel messages in a text widget
                ui->messages->clear();
                for (auto it =channelMessages.begin() ; it != channelMessages.end(); ++it) {
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
                for (auto it = pvMessages.begin(); it != pvMessages.end(); ++it) {
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
    }catch (const ExceptionHandler &e) { //handle these later
        QMessageBox::critical(this, "Error", e.message());
    }
}

//add to page
void loggedinpage::addtopage(const std::vector<std::unique_ptr<DTO>>& List){
    for (const auto& item : List) {
        const auto& Name = item->getName();
        const auto& Title = item->getTitle();
        // Check if an item with the same name already exists in the list widget
        bool found = false;
        for (int i = 0; i < ui->allchats->count(); i++) {
            QListWidgetItem* existingItem = ui->allchats->item(i);
            if (existingItem->text().startsWith(Title + ": " + Name)) {
                found = true;
                break;
            }
        }
        // If a match is not found, add the new item to the list widget
        if (!found) {
            QListWidgetItem* newItem = new QListWidgetItem(Title + ": " + Name);
            ui->allchats->addItem(newItem);
        }
    }
}

void loggedinpage::on_joingroupbtton_clicked()
{
    bool ok;
    QString inputText = QInputDialog::getText(this, "Input Dialog", "Enter input:", QLineEdit::Normal, "", &ok);
    if (ok && !inputText.isEmpty()) {
        QString response = groupRepo.join("6f72830134afcffe5fefba61c3216931" , inputText);
        if (response == "Successfully Joined" ){
            QMessageBox::information(this , "Information" , response);
            updatelists();
        }else {
            QMessageBox::critical(this , "Error" , response);
        }
    }
}


void loggedinpage::on_creategroupbutton_clicked()
{
    bool ok;
    QString inputText = QInputDialog::getText(this, "Input Dialog", "Enter input:", QLineEdit::Normal, "", &ok);
    if (ok && !inputText.isEmpty()) {
        QString response = groupRepo.create("6f72830134afcffe5fefba61c3216931" , inputText);
        if (response == "Group Created Successfully"){
            QMessageBox::information(this , "Information" , response);
            updatelists();
        }else {
            QMessageBox::critical(this , "Error" , response);
        }
    }
}



void loggedinpage::on_sendmessagebutton_clicked()
{
    if (selected.first == "group"){
        QString inputText = ui->sendmessageLE->text();
        QString response = groupRepo.sendMessage("6f72830134afcffe5fefba61c3216931" , selected.second ,inputText);
        if(response =="Message Sent Successfully" ){
            QMessageBox::information(this , "Information" , response);
            updateGroupMessages();
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
        }else {
            QMessageBox::critical(this , "Error" , response);
        }
    }else if (selected.first == "channel"){
        QString inputText = ui->sendmessageLE->text();
        QString response = channelRepo.sendMessage("6f72830134afcffe5fefba61c3216931" , selected.second ,inputText);
        if (response == "Message Successfully Sent"){
            QMessageBox::information(this , "Information" , response);
            updateChannelMessages();
            for (auto& channelPtr : channelList) {
                if (channelPtr->getName() == selected.second) {
                    // Get the channel messages from the found group object
                    QMultiMap<QString, QPair<QString , QString>> channelMessages = channelPtr->getMessages();
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
        }else {
            QMessageBox::critical(this , "Error" , response);
        }
    }else if (selected.first == "pv"){
        QString inputText = ui->sendmessageLE->text();
        QString response = pvRepo.sendMessage("6f72830134afcffe5fefba61c3216931" , selected.second ,inputText);
        if (response == "Message Sent Successfully"){
            updatePvMessages();
            QMessageBox::information(this , "Information" , response);
            updatePvMessages();
            for (auto& pvPtr : pvList) {
                if (pvPtr->getName() == selected.second) {
                    // Get the pv messages from the found group object
                    QMultiMap<QString, QPair<QString , QString>> pvMessages = pvPtr->getMessages();
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
        }else {
            QMessageBox::critical(this , "Error" , response);
        }
    }else if (selected.first == ""){
        QMessageBox::critical(this , "Error" , "You haven't selected a chat yet");
    }

}


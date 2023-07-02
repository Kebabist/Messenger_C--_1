#include "loggedinpage.h"
#include "mainwindow.h"
#include "exceptionhandler.h"
#include <QVector>
#include "ui_loggedinpage.h"
#include <QInputDialog>
#include <qmessagebox.h>
#include <QTimer>

loggedinpage::loggedinpage(Client& client,
                           GroupRepository& groupRepo,
                           ChannelRepository& channelRepo,
                           PvRepository& pvRepo,
                           QWidget* parent) :
    QWidget(parent),
    client(client),
    ui(new Ui::loggedinpage),
    groupRepo(groupRepo),
    channelRepo(channelRepo),
    pvRepo(pvRepo)
{
    ui->setupUi(this);
    connect(ui->allchats, &QListWidget::itemClicked, this, &loggedinpage::handleListItemClicked);
    ui->dockWidget->setTitleBarWidget(ui->widget_3);

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


//list updator function
void loggedinpage::updatelists(){
    groupRepo.getList(client.getToken());
    channelRepo.getList(client.getToken());
    pvRepo.getList(client.getToken());
    addtopage(); // Add group chats to the list widget
}
//update group messages
void loggedinpage::updateGroupMessages(){
    for(auto &groupPtr : groupRepo.get_List()){
        groupRepo.getChats(client.getToken() , groupPtr->getName());
        QMultiMap<QString, QPair<QString , QString>> groupMessages = groupPtr->getMessages();
    }
}

//update channel messages
void loggedinpage::updateChannelMessages(){
    for(auto &channelPtr : channelRepo.get_List()){
        channelRepo.getChats(client.getToken() , channelPtr->getName());
        QMultiMap<QString, QPair<QString , QString>> channelMessages = channelPtr->getMessages();
    }
}

//update pv messages
void loggedinpage::updatePvMessages(){
    for(auto &p : pvRepo.get_List()){
        pvRepo.getChats(client.getToken() , p->getName());
        QMultiMap<QString, QPair<QString , QString>> pvMessages = p->getMessages();
    }
}


//destructor
loggedinpage::~loggedinpage()
{
    delete ui;
}

//toggle the dock widget
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



//handle the clicked item
//handle the clicked item
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

    // Delete the last timer
    if (updateTimer != nullptr) {
        updateTimer->stop();
        updateTimer->deleteLater();
        updateTimer = nullptr;
    }
    // Create a new timer for updating the selected chat
    updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &loggedinpage::updateSelectedChat);
    updateTimer->start(5000);
}

void loggedinpage::updateSelectedChat()
{
    ui->messages->clear();
    if (selected.first == "group" && selected.second != ""){
        // Find the group object from the grouplist that matches the clicked group name
        for (auto& groupPtr : groupRepo.get_List()) {
            if (groupPtr->getName() == selected.second) {
                // Show the group messages in a text widget
                for (auto it =groupPtr->getMessages().begin(); it != groupPtr->getMessages().end(); ++it) {
                    QString sender = it.value().first;
                    QString text = it.value().second;
                    ui->messages->appendPlainText(sender + ": " + text);
                }
                break;
            }
        }
    } else if (selected.first == "channel" && selected.second != "") {
        // Find the channel object from the channellist that matches the clicked channel name
        for (auto& channelPtr : channelRepo.get_List()) {
            if (channelPtr->getName() == selected.second) {
                // Show the channel messages in a text widget
                for (auto it = channelPtr->getMessages().begin(); it != channelPtr->getMessages().end(); ++it) {
                    QString sender = it.value().first;
                    QString text = it.value().second;
                    ui->messages->appendPlainText(sender + ": " + text);
                }
                break;
            }
        }
    }
    else if (selected.first == "pv" && selected.second != "") {
        // Find the PV object from the PV_list that matches the clicked PV name
        for (auto& pvPtr : pvRepo.get_List()) {
            if (pvPtr->getName() == selected.second) {
                // Show the pv messages in a text widget
                for (auto it = pvPtr->getMessages().begin(); it != pvPtr->getMessages().end(); ++it) {
                    QString sender = it.value().first;
                    QString text = it.value().second;
                    ui->messages->appendPlainText(sender + ": " + text);
                }
                break;
            }
        }
    }
}

//logout
void loggedinpage::on_logoutbutton_clicked()
{
    try {
        QPair<QString , QString> response = client.Logout(); // Pass the correct password parameter
        QMessageBox::information(this, "Information", response.second);
        emit logoutbuttonclicked();
    }catch (const ExceptionHandler &e) { //handle these later
        QMessageBox::critical(this, "Error", e.message());
    }
}

//add to page
void loggedinpage::addtopage(){
   std::vector<Repository*> repos = { &groupRepo, &channelRepo, &pvRepo };
   for (std::size_t i = 0; i < repos.size(); ++i) {
        const std::vector<std::unique_ptr<DTO>>& List =repos[i]->get_List();
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
}

//join group button
void loggedinpage::on_joingroupbtton_clicked()
{
    bool ok;
    QString inputText = QInputDialog::getText(this, "Input Dialog", "Enter input:", QLineEdit::Normal, "", &ok);
    if (ok && !inputText.isEmpty()) {
        QString response = groupRepo.join(client.getToken() , inputText);
        if (response == "Successfully Joined" ){
            QMessageBox::information(this , "Information" , response);
            updatelists();
        }else {
            QMessageBox::critical(this , "Error" , response);
        }
    }
}

//create group button
void loggedinpage::on_creategroupbutton_clicked()
{
    bool ok;
    QString inputText = QInputDialog::getText(this, "Input Dialog", "Enter input:", QLineEdit::Normal, "", &ok);
    if (ok && !inputText.isEmpty()) {
        QString response = groupRepo.create(client.getToken() , inputText);
        if (response == "Group Created Successfully"){
            QMessageBox::information(this , "Information" , response);
            updatelists();
        }else {
            QMessageBox::critical(this , "Error" , response);
        }
    }
}

//join channel button
void loggedinpage::on_joinchannelbutton_clicked()
{
    bool ok;
    QString inputText = QInputDialog::getText(this, "Input Dialog", "Enter input:", QLineEdit::Normal, "", &ok);
    if (ok && !inputText.isEmpty()) {
        QString response = channelRepo.join(client.getToken() , inputText);
        if (response == "Successfully Joined"){
            QMessageBox::information(this , "Information" , response);
            updatelists();
        }else {
            QMessageBox::critical(this , "Error" , response);
        }
    }
}

//create new channel button
void loggedinpage::on_createchannelbutton_clicked()
{
    bool ok;
    QString inputText = QInputDialog::getText(this, "Input Dialog", "Enter input:", QLineEdit::Normal, "", &ok);
    if (ok && !inputText.isEmpty()) {
        QString response = channelRepo.create(client.getToken() , inputText);
        if (response == "Channel Created Successfully"){
            QMessageBox::information(this , "Information" , response);
            updatelists();
        }else {
            QMessageBox::critical(this , "Error" , response);
        }
    }
}

//start chat with a new user
void loggedinpage::on_newchatbutton_clicked()
{
    bool ok;
    QString inputText = QInputDialog::getText(this, "Input Dialog", "Enter recipient name:", QLineEdit::Normal, "", &ok);
    if (ok && !inputText.isEmpty()) {
        QString body = QInputDialog::getMultiLineText(this, "Input Dialog", "Enter message body:");
        QString response = pvRepo.sendMessage(client.getToken(), inputText, body);
        if (response == "Message Sent Successfully"){
            updatelists();
            QMessageBox::information(this , "Information" , response);
            updatePvMessages();
            for (auto& pvPtr : pvRepo.get_List()) {
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
    }
}


//send message to the selected item
void loggedinpage::on_sendmessagebutton_clicked()
{
    if (selected.first == "group"){
        QString inputText = ui->sendmessageLE->text();
        QString response = groupRepo.sendMessage(client.getToken() , selected.second ,inputText);
        if(response =="Message Sent Successfully" ){
            QMessageBox::information(this , "Information" , response);
            updateGroupMessages();
            for (auto& g : groupRepo.get_List()) {
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
        QString response = channelRepo.sendMessage(client.getToken() , selected.second ,inputText);
        if (response == "Message Successfully Sent"){
            QMessageBox::information(this , "Information" , response);
            updateChannelMessages();
            for (auto& channelPtr : channelRepo.get_List()) {
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
        QString response = pvRepo.sendMessage(client.getToken() , selected.second ,inputText);
        if (response == "Message Sent Successfully"){
            updatePvMessages();
            QMessageBox::information(this , "Information" , response);
            updatePvMessages();
            for (auto& pvPtr : pvRepo.get_List()) {
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



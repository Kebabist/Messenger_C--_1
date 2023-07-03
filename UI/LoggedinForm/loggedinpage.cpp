#include "loggedinpage.h"
#include "ui_loggedinpage.h"
#include <QInputDialog>
#include <qmessagebox.h>
#include <QVector>
#include <QTimer>

loggedinpage::loggedinpage(Client& client,
                           GroupRepository& groupRepo,
                           ChannelRepository& channelRepo,
                           PvRepository& pvRepo,
                           QWidget* parent) :
    QWidget(parent),
    client(client),
    existingGroupMessages("") ,
    existingChannelMessages(""),
    existingPvMessages(""),
    ui(new Ui::loggedinpage),
    groupRepo(groupRepo),
    channelRepo(channelRepo),
    pvRepo(pvRepo),
    stopThreads(false)
{
    try{
        ui->setupUi(this);
        setWindowTitle("Messenger");
        connect(this, &loggedinpage::loggedinpageClosed, this, &loggedinpage::handleLoggedinpageClosed);
        connect(ui->allchats, &QListWidget::itemClicked, this, &loggedinpage::handleListItemClicked);
        ui->dockWidget->setTitleBarWidget(ui->widget_3);
    }catch (...) {
        qDebug() << "Unknown exception caught in mainwindow";
    }
    connect(ui->allchats, &QListWidget::itemClicked, this, &loggedinpage::handleListItemClicked);
    ui->dockWidget->setTitleBarWidget(ui->widget_3);
    QShortcut* shortcut = new QShortcut(QKeySequence(Qt::Key_Return), this);
    shortcut->setContext(Qt::WidgetWithChildrenShortcut);
    ui->messages->setVerticalScrollBar(ui->verticalScrollBar);
    ui->verticalScrollBar->setValue(ui->verticalScrollBar->maximum());
    // Connect enter to sendbutton
    connect(shortcut, &QShortcut::activated, ui->sendmessagebutton, [this]() {
        ui->sendmessagebutton->click();
    });
    updateTimer = new QTimer(nullptr);

    QMutex mutex;
    QWaitCondition waitCondition;

    QThreadPool* threadPool = QThreadPool::globalInstance();
    threadPool->setMaxThreadCount(4);

    QFuture<void> future1 = QtConcurrent::run(threadPool, [&]() {
        while (!stopThreads) {
            try {
                updatelists();
                ui->usernamelabel->setText("logged in as : " + client.getUsername()); // Update the text with the user's name
            } catch (...) {
                // Handle exception
                qDebug()<<"Exception @ future1";
            }
            QThread::msleep(3000);
        }
        // Signal the wait condition and release the mutex when the thread is finished
        mutex.lock();
        waitCondition.wakeAll();
        mutex.unlock();
    });

    // Execute the update group messages function asynchronously
    QFuture<void> future2 = QtConcurrent::run(threadPool, [&]() {
        while (!stopThreads) {
            try {
                updateGroupMessages();
            } catch (...) {
                // Handle exception
                qDebug()<<"Exception @ future1";
            }
            QThread::msleep(3000);
        }
        // Signal the wait condition and release the mutex when the thread is finished
        mutex.lock();
        waitCondition.wakeAll();
        mutex.unlock();
    });


    // Execute the update channel messages function asynchronously
    QFuture<void> future3 = QtConcurrent::run(threadPool, [&]() {
        while (!stopThreads) {
            try {
                updateChannelMessages();
            } catch (...) {
                // Handle exception
                qDebug()<<"Exception @ future1";
            }
            QThread::msleep(3000);
        }
        // Signal the wait condition and release the mutex when the thread is finished
        mutex.lock();
        waitCondition.wakeAll();
        mutex.unlock();
    });
    // Execute the update private messages function asynchronously
    QFuture<void> future4 = QtConcurrent::run(threadPool, [&]() {
        while (!stopThreads) {
            try {
                updatePvMessages();
            } catch (...) {
                // Handle exception
                qDebug()<<"Exception @ future1";
            }
            QThread::msleep(3000);
        }
        // Signal the wait condition and release the mutex when the thread is finished
        mutex.lock();
        waitCondition.wakeAll();
        mutex.unlock();
    });
    // Connect logout button to stop threads
    connect(ui->logoutbutton, &QPushButton::clicked, this, [&]() {
        try{
            stopThreads = true;
            // Lock the mutex and wait for the threads to finish
            mutex.lock();
            waitCondition.wakeAll(); // Wake all waiting threads
            mutex.unlock();

            QFutureWatcher<void> watcher;
            // Wait for all futures to finish
            watcher.setFuture(future1);
            watcher.setFuture(future2);
            watcher.setFuture(future3);
            watcher.setFuture(future4);
            watcher.waitForFinished();
            // Wait for all threads in the thread pool to finish executing
            QThreadPool::globalInstance()->waitForDone();

            // Clear the thread pool to delete all threads
            QThreadPool::globalInstance()->clear();
            loggedinpage::on_logoutbutton_clicked();
        }catch (...) {
            qDebug() << "Unknown exception caught in loggedin window constructor";
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
        ui->messages->clear();
        existingGroupMessages.clear();
    }else{
        index = text.indexOf(substrch);
        if (index != -1) {
            text.remove(index, substrch.length());
            channelName = text;
            selected = qMakePair("channel" , channelName);
            ui->messages->clear();
            existingChannelMessages.clear();
        }else {
            index = text.indexOf(substrpv);
            if (index != -1) {
                text.remove(index, substrpv.length());
                pvName = text;
                selected = qMakePair("pv" , pvName);
                ui->messages->clear();
                existingPvMessages.clear();
            }
        }
    }

    // Delete the last timer
    if (updateTimer != nullptr) {
        if (updateTimer->isActive()) {
            updateTimer->stop();
        }
        updateTimer->deleteLater();
        updateTimer = nullptr;
    }
    // Create a new timer for updating the selected chat
    updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &loggedinpage::updateSelectedChat);
    updateTimer->start(500);
}

void loggedinpage::updateSelectedChat()
{
    if (selected.first == "group" && selected.second != "") {
        // Find the group object from the grouplist that matches the clicked group name
        for (auto& groupPtr : groupRepo.get_List()) {
            if (groupPtr->getName() == selected.second) {
                if (existingGroupMessages == ""){
                    existingGroupMessages = ui->messages->toPlainText();
                    // Show the group messages in a text widget
                    for (auto it = groupPtr->getMessages().begin(); it != groupPtr->getMessages().end(); ++it) {
                        QString timestamp = it.key();

                        QDateTime dateTime = QDateTime::fromString(timestamp, "yyyyMMddhhmmss");
                        QString formattedTimestamp = dateTime.toString("yyyy-MM-dd hh:mm:ss");

                        QString sender = it.value().first;
                        QString text = it.value().second;
                        QString senderColor = " #00ffe8  "; // Color for the sender
                        QString textColor = " #13ff00 "; // Color for the message text
                        QString formattedMessage = QString("<p><span style=\"color: %1;\">%2:</span> <span style=\"color: %3;\">%4</span><span style=\"color: #999;\">"
                                                           "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t%5</span></p>")
                                                       .arg(senderColor)
                                                       .arg(sender)
                                                       .arg(textColor)
                                                       .arg(text)
                                                       .arg(formattedTimestamp);

                        QString chatItem = QString("%1 : %2\n%3").arg(sender, text, formattedTimestamp);
                        existingGroupMessages += chatItem;
                        ui->messages->moveCursor(QTextCursor::End);
                        ui->messages->insertHtml(formattedMessage);
                        ui->messages->insertPlainText("\n");

                    }
                }else {
                    // Show the group messages in a text widget
                    for (auto it = groupPtr->getMessages().begin(); it != groupPtr->getMessages().end(); ++it) {
                        QString timestamp = it.key();

                        QDateTime dateTime = QDateTime::fromString(timestamp, "yyyyMMddhhmmss");
                        QString formattedTimestamp = dateTime.toString("yyyy-MM-dd hh:mm:ss");

                        QString sender = it.value().first;
                        QString text = it.value().second;
                        QString senderColor = " #00ffe8  "; // Color for the sender
                        QString textColor = " #13ff00 "; // Color for the message text
                        QString formattedMessage = QString("<p><span style=\"color: %1;\">%2:</span> <span style=\"color: %3;\">%4</span><span style=\"color: #999;\">"
                                                           "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t%5</span></p>")
                                                       .arg(senderColor)
                                                       .arg(sender)
                                                       .arg(textColor)
                                                       .arg(text)
                                                       .arg(formattedTimestamp);

                        QString chatItem = QString("%1 : %2\n%3").arg(sender, text, formattedTimestamp);
                        // Check if the message isn't already in the QTextEdit
                        if (!existingGroupMessages.contains(chatItem)) {
                            ui->messages->moveCursor(QTextCursor::End);
                            ui->messages->insertHtml(formattedMessage);
                            ui->messages->insertPlainText("\n");
                            existingGroupMessages += chatItem;
                        }
                }
                }
                break;
            }
        }
    } else if (selected.first == "channel" && selected.second != "") {
        // Find the channel object from the channellist that matches the clicked channel name
        for (auto& channelPtr : channelRepo.get_List()) {
            if (channelPtr->getName() == selected.second) {
                if (existingChannelMessages == "") {
                existingChannelMessages = ui->messages->toPlainText();
                // Show the channel messages in a text widget
                for (auto it = channelPtr->getMessages().begin(); it != channelPtr->getMessages().end(); ++it) {
                        QString timestamp = it.key();

                        QDateTime dateTime = QDateTime::fromString(timestamp, "yyyyMMddhhmmss");
                        QString formattedTimestamp = dateTime.toString("yyyy-MM-dd hh:mm:ss");

                        QString sender = it.value().first;
                        QString text = it.value().second;
                        QString senderColor = " #00ffe8  "; // Color for the sender
                        QString textColor = " #13ff00 "; // Color for the message text
                        QString formattedMessage = QString("<p><span style=\"color: %1;\">%2:</span> <span style=\"color: %3;\">%4</span><span style=\"color: #999;\">"
                                                           "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t%5</span></p>")
                                                       .arg(senderColor)
                                                       .arg(sender)
                                                       .arg(textColor)
                                                       .arg(text)
                                                       .arg(formattedTimestamp);

                        QString chatItem = QString("%1 : %2\n%3").arg(sender, text, formattedTimestamp);
                        existingChannelMessages += chatItem;
                        ui->messages->moveCursor(QTextCursor::End);
                        ui->messages->insertHtml(formattedMessage);
                        ui->messages->insertPlainText("\n");
                }
                } else {
                // Show the channel messages in a text widget
                for (auto it = channelPtr->getMessages().begin(); it != channelPtr->getMessages().end(); ++it) {
                        QString timestamp = it.key();

                        QDateTime dateTime = QDateTime::fromString(timestamp, "yyyyMMddhhmmss");
                        QString formattedTimestamp = dateTime.toString("yyyy-MM-dd hh:mm:ss");

                        QString sender = it.value().first;
                        QString text = it.value().second;
                        QString senderColor = " #00ffe8  "; // Color for the sender
                        QString textColor = " #13ff00 "; // Color for the message text
                        QString formattedMessage = QString("<p><span style=\"color: %1;\">%2:</span> <span style=\"color: %3;\">%4</span><span style=\"color: #999;\">"
                                                           "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t%5</span></p>")
                                                       .arg(senderColor)
                                                       .arg(sender)
                                                       .arg(textColor)
                                                       .arg(text)
                                                       .arg(formattedTimestamp);

                        QString chatItem = QString("%1 : %2\n%3").arg(sender, text, formattedTimestamp);
                        // Check if the message isn't already in the QTextEdit
                        if (!existingChannelMessages.contains(chatItem)) {
                            ui->messages->moveCursor(QTextCursor::End);
                            ui->messages->insertHtml(formattedMessage);
                            ui->messages->insertPlainText("\n");
                            existingChannelMessages += chatItem;
                        }
                }
                }
                break;
            }
        }
    } else if (selected.first == "pv" && selected.second != "") {
        // Find the PV object from the PV_list that matches the clicked PV name
        for (auto& pvPtr : pvRepo.get_List()) {
            if (pvPtr->getName() == selected.second) {
                if (existingPvMessages == "") {
                existingPvMessages = ui->messages->toPlainText();
                // Show the pv messages in a text widget
                for (auto it = pvPtr->getMessages().begin(); it != pvPtr->getMessages().end(); ++it) {
                        QString timestamp = it.key();

                        QDateTime dateTime = QDateTime::fromString(timestamp, "yyyyMMddhhmmss");
                        QString formattedTimestamp = dateTime.toString("yyyy-MM-dd hh:mm:ss");

                        QString sender = it.value().first;
                        QString text = it.value().second;
                        QString senderColor = " #00ffe8  "; // Color for the sender
                        QString textColor = " #13ff00 "; // Color for the message text
                        QString formattedMessage = QString("<p><span style=\"color: %1;\">%2:</span> <span style=\"color: %3;\">%4</span><span style=\"color: #999;\">"
                                                           "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t%5</span></p>")
                                                       .arg(senderColor)
                                                       .arg(sender)
                                                       .arg(textColor)
                                                       .arg(text)
                                                       .arg(formattedTimestamp);

                        QString chatItem = QString("%1 : %2\n%3").arg(sender, text, formattedTimestamp);
                        existingPvMessages += chatItem;
                        ui->messages->moveCursor(QTextCursor::End);
                        ui->messages->insertHtml(formattedMessage);
                        ui->messages->insertPlainText("\n");
                }
                } else {
                // Show the pv messages in a text widget
                for (auto it = pvPtr->getMessages().begin(); it != pvPtr->getMessages().end(); ++it) {
                        QString timestamp = it.key();

                        QDateTime dateTime = QDateTime::fromString(timestamp, "yyyyMMddhhmmss");
                        QString formattedTimestamp = dateTime.toString("yyyy-MM-dd hh:mm:ss");

                        QString sender = it.value().first;
                        QString text = it.value().second;
                        QString senderColor = " #00ffe8  "; // Color for the sender
                        QString textColor = " #13ff00 "; // Color for the message text
                        QString formattedMessage = QString("<p><span style=\"color: %1;\">%2:</span> <span style=\"color: %3;\">%4</span><span style=\"color: #999;\">"
                                                           "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t%5</span></p>")
                                                       .arg(senderColor)
                                                       .arg(sender)
                                                       .arg(textColor)
                                                       .arg(text)
                                                       .arg(formattedTimestamp);

                        QString chatItem = QString("%1 : %2\n%3").arg(sender, text, formattedTimestamp);
                        // Check if the message isn't already in the QTextEdit
                        if (!existingPvMessages.contains(chatItem)) {
                            ui->messages->moveCursor(QTextCursor::End);
                            ui->messages->insertHtml(formattedMessage);
                            ui->messages->insertPlainText("\n");
                            existingPvMessages += chatItem;
                        }
                }
                }
                break;
            }
        }
    }
}

//slot for logout signal
void loggedinpage::on_logoutbutton_clicked()
{
    try {
        disconnect(this, &loggedinpage::loggedinpageClosed, this, &loggedinpage::handleLoggedinpageClosed);
        QPair<QString , QString> response = client.Logout(); // Pass the correct password parameter
        if (response.second == "Logged Out Successfully"){
            QMessageBox::information(this, "Information", response.second);
            removeAll();
            emit logoutbuttonclicked();
        }/*else{
            throw response.second;
        }*/
    }/*catch (const std::exception& e) {
        qDebug() << "Exception caught in logout clicked:" << e.what();
    }*/catch (...) {
        qDebug() << "Unknown exception caught in on_logoutbutton_clicked";
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
                ui->allchats->sortItems();
            }
        }
    }
}

//join group button
void loggedinpage::on_joingroupbtton_clicked()
{
    bool ok;
    QInputDialog inputDialog(this);
    inputDialog.setStyleSheet("background-color: rgb(24, 52, 81); color: rgb(255, 151, 23); QPushButton { background-color: rgb(24, 52, 81); color: rgb(255, 151, 23); }");
    inputDialog.setInputMode(QInputDialog::TextInput);
    inputDialog.setLabelText("whats the name?");
    inputDialog.setTextValue("");
    inputDialog.setWindowTitle("I'm gonna find it");
    inputDialog.setOkButtonText("OK");
    inputDialog.setCancelButtonText("Cancel");
    if (inputDialog.exec() == QDialog::Accepted) {
        QString inputText = inputDialog.textValue();
        QString response = groupRepo.join(client.getToken() , inputText);
        if (response == "Successfully Joined" ){
            QMessageBox::information(this , "Information" , response);
        } else {
            QMessageBox::critical(this , "Error" , response);
        }
    }
}
//create group button
void loggedinpage::on_creategroupbutton_clicked()
{
    bool ok;
    QInputDialog inputDialog(this);
    inputDialog.setStyleSheet("background-color: rgb(24, 52, 81); color: rgb(255, 151, 23); QPushButton { background-color: rgb(24, 52, 81); color: rgb(255, 151, 23); }");
    inputDialog.setInputMode(QInputDialog::TextInput);
    inputDialog.setLabelText("whats the name?");
    inputDialog.setTextValue("");
    inputDialog.setWindowTitle("Find A Cool Name");
    inputDialog.setOkButtonText("OK");
    inputDialog.setCancelButtonText("Cancel");
    if (inputDialog.exec() == QDialog::Accepted) {
        QString inputText = inputDialog.textValue();
        QString response = groupRepo.create(client.getToken() , inputText);
        if (response == "Group Created Successfully"){
            QMessageBox::information(this , "Information" , response);
        }else {
            QMessageBox::critical(this , "Error" , response);
        }
    }
}

//join channel button
void loggedinpage::on_joinchannelbutton_clicked()
{
    bool ok;
    QInputDialog inputDialog(this);
    inputDialog.setStyleSheet("background-color: rgb(24, 52, 81); color: rgb(255, 151, 23); QPushButton { background-color: rgb(24, 52, 81); color: rgb(255, 151, 23); }");
    inputDialog.setInputMode(QInputDialog::TextInput);
    inputDialog.setLabelText("whats the name?");
    inputDialog.setTextValue("");
    inputDialog.setWindowTitle("I'm gonna find it");
    inputDialog.setOkButtonText("OK");
    inputDialog.setCancelButtonText("Cancel");
    if (inputDialog.exec() == QDialog::Accepted) {
        QString inputText = inputDialog.textValue();
        QString response = channelRepo.join(client.getToken() , inputText);
        if (response == "Successfully Joined"){
            QMessageBox::information(this , "Information" , response);
        }else {
            QMessageBox::critical(this , "Error" , response);
        }
    }
}

//create new channel button
void loggedinpage::on_createchannelbutton_clicked()
{
    bool ok;
    QInputDialog inputDialog(this);
    inputDialog.setStyleSheet("background-color: rgb(24, 52, 81); color: rgb(255, 151, 23); QPushButton { background-color: rgb(24, 52, 81); color: rgb(255, 151, 23); }");
    inputDialog.setInputMode(QInputDialog::TextInput);
    inputDialog.setLabelText("whats the name?");
    inputDialog.setTextValue("");
    inputDialog.setWindowTitle("Find A Cool Name");
    inputDialog.setOkButtonText("OK");
    inputDialog.setCancelButtonText("Cancel");
    if (inputDialog.exec() == QDialog::Accepted) {
        QString inputText = inputDialog.textValue();
        QString response = channelRepo.create(client.getToken() , inputText);
        if (response == "Channel Created Successfully"){
            QMessageBox::information(this , "Information" , response);
        }else {
            QMessageBox::critical(this , "Error" , response);
        }
    }
}

//start chat with a new user
void loggedinpage::on_newchatbutton_clicked()
{
    bool ok;
    QInputDialog inputDialog(this);
    inputDialog.setStyleSheet("background-color: rgb(24, 52, 81); color: rgb(255, 151, 23); QPushButton { background-color: rgb(24, 52, 81); color: rgb(255, 151, 23); }");
    inputDialog.setInputMode(QInputDialog::TextInput);
    inputDialog.setLabelText("Give us the Name we'll deliver");
    inputDialog.setTextValue("");
    inputDialog.setWindowTitle("Just say who ? ");
    inputDialog.setOkButtonText("OK");
    inputDialog.setCancelButtonText("Cancel");
    if (inputDialog.exec() == QDialog::Accepted) {
        QString destinationUser = inputDialog.textValue();
        bool ok;
        QFont font;
        font.setFamily("Courier");
        font.setPointSize(10);
        QInputDialog multiInputDialog(this);
        multiInputDialog.setStyleSheet("background-color: rgb(24, 52, 81); color: rgb(255, 151, 23); QPushButton { background-color: rgb(24, 52, 81); color: rgb(255, 151, 23); }");
        multiInputDialog.setInputMode(QInputDialog::TextInput);
        multiInputDialog.setLabelText("Enter message body:");
        multiInputDialog.setTextValue("");
        multiInputDialog.setWindowTitle("To " + destinationUser);
        multiInputDialog.setOkButtonText("OK");
        multiInputDialog.setCancelButtonText("Cancel");
        QTextEdit *textEdit = multiInputDialog.findChild<QTextEdit *>();
        if (textEdit) {
            textEdit->setFont(font);
        }
        QString body = "";
        if (multiInputDialog.exec() == QDialog::Accepted) {
            body = multiInputDialog.textValue();
        }
        QString response = pvRepo.sendMessage(client.getToken(), destinationUser, body);
        if (response == "Message Sent Successfully") {
            updatelists();
            QMessageBox::information(this , "Information" , response);
        } else {
            QMessageBox::critical(this , "Error" , response);
        }
    }
}


//send message to the selected item
void loggedinpage::on_sendmessagebutton_clicked()
{
    QString inputText = ui->sendmessageLE->text();
    if (!inputText.isEmpty()){
        if (selected.first == "group"){
                QString response = groupRepo.sendMessage(client.getToken() , selected.second ,inputText);
                if(response !="Message Sent Successfully" ){
                    QMessageBox::critical(this , "Error" , response);
                }
        }
        else if (selected.first == "channel"){
            QString response = channelRepo.sendMessage(client.getToken() , selected.second ,inputText);
            if (response != "Message Successfully Sent"){
                    QMessageBox::critical(this , "Error" , response);
            }
        }else if (selected.first == "pv"){
            QString response = pvRepo.sendMessage(client.getToken() , selected.second ,inputText);
            if (response != "Message Sent Successfully"){
                QMessageBox::critical(this , "Error" , response);
            }
        }
        ui->sendmessageLE->clear();
    }else {
        QMessageBox::critical(this, "Error" , "The input cant be empty!");
    }
}

// handleLoggedinpageClosed slot
void loggedinpage::handleLoggedinpageClosed()
{
    // Called when the loggedinpage is closed
    writeAll();
}

void loggedinpage::closeEvent(QCloseEvent *event) {
    emit loggedinpageClosed();
    QWidget::closeEvent(event);
}

//Writes all files when program is closed
void loggedinpage::writeAll(){
    try{
        pvRepo.writeMessages();
        groupRepo.writeMessages();
        channelRepo.writeMessages();
        qDebug()<<"Wrote all chat Data on Disk";
    }catch (...) {
        qDebug() << "Unknown exception caught in WriteALL";
    }
}

//removes all user chat files/Directories on user logou
void loggedinpage::removeAll(){
    try{
        pvRepo.removeDir();
        groupRepo.removeDir();
        channelRepo.removeDir();
        qDebug()<<"removed all user files/Dirs on Disk";
    }catch (...) {
        qDebug() << "Unknown exception caught in RemoveALL";
    }
}

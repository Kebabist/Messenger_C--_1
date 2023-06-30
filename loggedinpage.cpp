#include "loggedinpage.h"
#include "mainwindow.h"
#include "exceptionhandler.h"
#include "ui_loggedinpage.h"
#include <qmessagebox.h>


loggedinpage::loggedinpage(Group& g, GroupRepository& gr, Client& client, QWidget* parent) :
    QWidget(parent),
    ui(new Ui::loggedinpage),
    cl(client),
    group(g),
    grouprepo(gr)
{
    ui->setupUi(this);
    connect(ui->toggleview, SIGNAL(clicked(bool)), this, SLOT(onToggleviewClicked(bool)));
    connect(ui->allchats, &QListWidget::itemClicked, this, &loggedinpage::handleListItemClicked);
    ui->dockWidget->setTitleBarWidget(ui->widget_3);
    QList<Group> groups = grouprepo.getGroup_list();
    addtopage(groups); // Add groups to the list widget
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
    QString groupName = item->text();

    // Find the group object from the group_list that matches the clicked group name
    Group group;
    for (auto& g : grouprepo.getGroup_list()) {
        if (g.getGroupname() == groupName) {
            group = g;
            break;
        }
    }

    // Get the group messages from the found group object
    QMultiMap<QString, QPair<QString , QString>> groupMessages = group.getGroupmessages();

    // Show the group messages in a text widget
    ui->messages->clear();
    for (QMultiMap<QString, QPair<QString , QString>>::Iterator it =groupMessages.begin() ; it != groupMessages.end(); ++it) {
        QString sender = it.value().first;
        QString text = it.value().second;
        ui->messages->appendPlainText(sender + ": " + text);
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

void loggedinpage::addtopage(const QList<Group>& groupList){
    for (const auto& groupName : groupList){
        QListWidgetItem* item = new QListWidgetItem(groupName.getGroupname());
        ui->allchats->addItem(item);
    }
}

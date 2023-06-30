#include "loggedinpage.h"
#include "exceptionhandler.h"
#include "ui_loggedinpage.h"
#include <qmessagebox.h>


loggedinpage::loggedinpage(Client &client, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loggedinpage) , cl(client)
{
    ui->setupUi(this);
    connect(ui->toggleview, SIGNAL(clicked(bool)), this, SLOT(onToggleviewClicked(bool)));
    connect(ui->allchats, &QListWidget::itemClicked, this, &loggedinpage::handleListItemClicked); //for the  text widget
    ui->dockWidget->setTitleBarWidget(ui->widget_3);
    QList<QString> groups = {"Group 1", "Group 2", "Group 3"};
    addtopage(groups);

}

loggedinpage::~loggedinpage()
{
    delete ui;
}

void loggedinpage::on_toggleview_clicked(bool checked)
{
    ui->dockWidget->setVisible(checked);
}

QMultiMap<QString, QString> group_messages = {
    {"Group 1", "adlfkakjfdl src : kebab"},
    {"Group 1", "afdsafdsafds src : kebab"},
    {"Group 1", "adlfkadsfafdafdsakjfdl src : kebab"},
    {"Group 1", "adlafdfkadsfafdsakjfdl src : kebab"},
    {"Group 1", "adlfafdsafdsfadskakjfdl src : kebab"},
    {"Group 1", "adlfadsfkaadsfafdskjfdl src : kebab"},
    {"Group 2", "aldkfafdsafdsfasdfalkdjs src : nima"},
    {"Group 3", "aflkdkafdsafdafdsalfdskald src : kebab"}
};


void loggedinpage::handleListItemClicked(QListWidgetItem* item)
{
    QString groupName = item->text();

    // Get the group messages from the group_messages map
    QList<QString> groupMessages = group_messages.values(groupName);

    // Show the group messages in a text widget
    ui->messages->clear();
    for (const auto& message : groupMessages){
        ui->messages->appendPlainText(message);
    }
}

void loggedinpage::on_logoutbutton_clicked()
{
    try {
        QPair<QString , QString> response = cl.Logout(); // Pass the correct password parameter
        QMessageBox::information(this, "Information", response.second);
        emit logoutbuttonclicked();
    }catch (const HttpHandlerException &e) {
        QMessageBox::critical(this, "Error", e.message());
    }
}


void loggedinpage::addtopage(const QList<QString>& groupList){
    for (const auto& groupName : groupList){
        QListWidgetItem* item = new QListWidgetItem(groupName);
        ui->allchats->addItem(item);
    }
}



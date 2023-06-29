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
    //connect(this, &loggedinpage::logoutbuttonclicked, this, &loggedinpage::handleLogoutButtonClicked);
    ui->dockWidget->setTitleBarWidget(ui->widget_3);
}

loggedinpage::~loggedinpage()
{
    delete ui;
}

void loggedinpage::on_toggleview_clicked(bool checked)
{
    ui->dockWidget->setVisible(checked);
}




void loggedinpage::on_logoutbutton_clicked()
{
    try {
        QPair<QString , QString> response = cl.Logout(cl.getUsername(), cl.getPassword()); // Pass the correct password parameter
        QMessageBox::information(this, "Information", response.second);
        emit logoutbuttonclicked();
    }catch (const HttpHandlerException &e) {
        QMessageBox::critical(this, "Error", e.message());
    }
}


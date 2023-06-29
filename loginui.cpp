#include "loginui.h"
#include "ui_loginui.h"
#include "client.h"
#include "exceptionhandler.h"
#include <QMessageBox>

loginui::loginui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loginui)
{
    ui->setupUi(this);
}

loginui::~loginui()
{
    delete ui;
}

//handle the submit button
void loginui::on_submitbutton_clicked()
{
    QString username = ui->usernameLE->text();
    QString password = ui->passwordLE->text();
    Client client(username , password);
    try {
        QPair<QString , QString> response = client.Login(username , password);
        if (response.second != "You are already logged in!"){
        QMessageBox::information(this, "Information", response.second);
        }else {
            throw response.second;
        }
        emit loginApproved(client);
    }catch (const HttpHandlerException &e) {
        QMessageBox::critical(this, "Error", e.message());
    }catch(QString f){
        QMessageBox::critical(this, "Error", f);
    }
}

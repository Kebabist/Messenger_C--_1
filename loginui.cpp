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
        QPair<QString , QString> response = client.Login();
        if (response.second == "Logged in Successfully"){
            QMessageBox::information(this, "Information", response.second);
            emit loginApproved(client);
        }else {
            throw response.second;
        }
    }catch (const ExceptionHandler &e) {
        QMessageBox::critical(this, "Error", e.message());
    }catch(QString f){
        QMessageBox::critical(this, "Error", f);
    }
}

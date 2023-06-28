#include "signupui.h"
#include "ui_signupui.h"
#include "client.h"
#include <QMessageBox>

signupui::signupui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::signupui)
{
    ui->setupUi(this);
}

signupui::~signupui()
{
    delete ui;
}

void signupui::on_submitbutton_clicked()
{
    QString username = ui->usernameLE->text();
    QString password = ui->passwordLE->text();
    QString firstname = ui->firstnameLE->text();
    QString lastname = ui->lastnameLE->text();
    Client cl(username , password , firstname , lastname);
    QPair<QString , QString> response = cl.Signup();
    if (response.first == "200"){
        QMessageBox::information(this, "Information", response.second);
        emit signupApproved();
    }else {
        QMessageBox::critical(this, "Error", response.second);
    }

}


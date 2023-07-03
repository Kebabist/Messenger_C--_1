#include "signupui.h"
#include "ui_signupui.h"
#include "client.h"
#include "exceptionhandler.h"
#include <QMessageBox>

signupui::signupui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::signupui)
{
    ui->setupUi(this);
    setWindowTitle("SignUp");
}

signupui::~signupui()
{
    delete ui;
}

//handle the submit button
void signupui::on_submitbutton_clicked()
{
    QString username = ui->usernameLE->text();
    QString password = ui->passwordLE->text();
    QString firstname = ui->firstnameLE->text();
    QString lastname = ui->lastnameLE->text();
    Client cl(username , password , firstname , lastname);
    try {
        QPair<QString , QString> response = cl.Signup();
        QMessageBox::information(this, "Information", response.second);
        emit signupApproved();
    }catch (const ExceptionHandler &e) {
        QMessageBox::critical(this, "Error", e.message());
    }
}


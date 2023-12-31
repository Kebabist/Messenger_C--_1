#include "signupui.h"
#include "ui_signupui.h"
#include "Client/client.h"
#include "ExceotionHandler/exceptionhandler.h"
#include <QMessageBox>

signupui::signupui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::signupui)
{   try{
        ui->setupUi(this);
        setWindowTitle("SignUp");
        QShortcut* shortcut = new QShortcut(QKeySequence(Qt::Key_Return), this);
        shortcut->setContext(Qt::WidgetWithChildrenShortcut);
        // Connect enter to sendbutton
        connect(shortcut, &QShortcut::activated, ui->submitbutton, [this]() {
            ui->submitbutton->click();
        });
    }catch (...) {
        qDebug() << "Unknown exception caught";
    }
}

signupui::~signupui()
{
    delete ui;
}

//handle the submit button
void signupui::on_submitbutton_clicked(){
    try{
        QString username = ui->usernameLE->text();
        QString password = ui->passwordLE->text();
        QString firstname = ui->firstnameLE->text();
        QString lastname = ui->lastnameLE->text();
        Client cl(username , password , firstname , lastname);
        QPair<QString , QString> response = cl.Signup();
        QMessageBox::information(this, "Information", response.second);
        emit signupApproved();
    }catch (const ExceptionHandler &e) {
        QMessageBox::critical(this, "Error", e.message());
    }
}


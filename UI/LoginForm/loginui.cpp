#include "loginui.h"
#include "ui_loginui.h"
#include "Client/client.h"
#include "ExceotionHandler/exceptionhandler.h"
#include <QMessageBox>

loginui::loginui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loginui)
{   try{
        ui->setupUi(this);
        setWindowTitle("Login");
        QShortcut* shortcut = new QShortcut(QKeySequence(Qt::Key_Return), this);
        shortcut->setContext(Qt::WidgetWithChildrenShortcut);
        // Connect enter to sendbutton
        connect(shortcut, &QShortcut::activated, ui->submitbutton, [this]() {
            ui->submitbutton->click();
        });
    }catch (...) {
        qDebug() << "Unknown exception caught in loginui constructor";
    }
}

loginui::~loginui()
{
    delete ui;
}

//handle the submit button
void loginui::on_submitbutton_clicked()
{   try{
        QString username = ui->usernameLE->text();
        QString password = ui->passwordLE->text();
        Client *client = new Client(username, password);
        try {
            QPair<QString , QString> response = client->Login();
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
    }catch (...) {
        qDebug() << "Unknown exception caught in on_submitbutton_clicked";
    }
}

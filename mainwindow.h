#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "signupui.h"
#include "loginui.h"
#include "loggedinpage.h"
#include "Client.h"
#include "exceptionhandler.h"
#include "group.h"
#include "grouprepository.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Group & , GroupRepository & , QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //buttons
    void on_signupbutton_clicked();
    void on_loginbutton_clicked();

    //handle the pages signals
    void handleSignupApproved();
    void handleloginApproved(Client& client);
    void handleLogoutClicked();

private:
    Ui::MainWindow *ui;
    //create signup page object
    signupui *signup;
    //create login page object
    loginui *login;
    //create loggedinpage object
    loggedinpage *loggedin;
    //group and grouprepo object
    Group group;
    GroupRepository grouprepo;

};
#endif // MAINWINDOW_H

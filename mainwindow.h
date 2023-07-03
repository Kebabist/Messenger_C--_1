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
#include "channel.h"
#include "channelrepository.h"
#include "pv.h"
#include "pvrepository.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Client& client , GroupRepository& groupRepo,
               ChannelRepository& channelRepo,
               PvRepository& pvRepo ,
               QWidget *parent = nullptr);
    ~MainWindow();
    void ClientState();

private slots:
    //buttons
    void on_signupbutton_clicked();
    void on_loginbutton_clicked();
    void handleLoggedinpageClosed();
    void handleAboutToQuit();

    //handle the pages signals
    void handleSignupApproved();
    void handleloginApproved(Client *loginClient);
    void handleLogoutClicked();

private:
    bool flag;
    Client& client;
    Ui::MainWindow *ui;
    //create signup page object
    signupui *signup;
    //create login page object
    loginui *login;
    //create loggedinpage object
    loggedinpage *loggedin;
    //group and grouprepo object
    GroupRepository& groupRepo;
    ChannelRepository& channelRepo;
    PvRepository& pvRepo;
};
#endif // MAINWINDOW_H

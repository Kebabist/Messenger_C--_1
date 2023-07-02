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
    MainWindow(const std::vector<std::unique_ptr<DTO>>& groupList,
               const std::vector<std::unique_ptr<DTO>>& pvList,
               const std::vector<std::unique_ptr<DTO>>& channelList,
               GroupRepository& groupRepo,
               ChannelRepository& channelRepo,
               PvRepository& pvRepo ,
               QWidget *parent = nullptr);
    ~MainWindow();
    void writeAll();
private slots:
    //buttons
    void on_signupbutton_clicked();
    void on_loginbutton_clicked();

    //handle the pages signals
    void handleSignupApproved();
    void handleloginApproved(Client& client);
    void handleLogoutClicked();
public slots:
    void onMainWindowClosed();

private:
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
    const std::vector<std::unique_ptr<DTO>>& pvList;
    const std::vector<std::unique_ptr<DTO>>& groupList;
    const std::vector<std::unique_ptr<DTO>>& channelList;

};
#endif // MAINWINDOW_H

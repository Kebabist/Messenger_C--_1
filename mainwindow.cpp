#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qmessagebox.h>


MainWindow::MainWindow( const std::vector<std::unique_ptr<DTO>>& passedgroupList,
                       const std::vector<std::unique_ptr<DTO>>& passedchannelList,
                       const std::vector<std::unique_ptr<DTO>>& passedpvList , QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , pvList(passedpvList)
    , groupList(passedgroupList)
    , channelList(passedchannelList)
{

    ui->setupUi(this);
    Client client;
    client.ReadClient();
    if (!client.getToken().isEmpty()) {
        // The client data was successfully read and contains a token, redirect to the logged in page
        //QWidget* loggedInPageParent = new QWidget();
        loggedin = new loggedinpage( groupList, channelList , pvList , client );
        loggedin->show();
        connect(loggedin, &loggedinpage::logoutbuttonclicked, this, &MainWindow::handleLogoutClicked);
        //loggedin->setWindowFlags(Qt::Tool);
        // Hide the main window after the logged in window is shown
        loggedin->show();
        loggedin->isActiveWindow();
        return;
    } else {
        // The client data could not be read or does not contain a token, stay on the main window
        show();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

//handle signup signal
void MainWindow::handleSignupApproved()
{
    signup->close(); // Close the signup page
    // Show or perform any actions related to the start page
}

//handle login signal
void MainWindow::handleloginApproved(Client& client)
{

    login->close(); // Close the login page
    loggedin = new loggedinpage(groupList, channelList , pvList , client);
    loggedin->show();
    connect(loggedin, &loggedinpage::logoutbuttonclicked, this, &MainWindow::handleLogoutClicked);
}

void MainWindow::handleLogoutClicked()
{
    loggedin->close(); // Close the loggedin page

}

//open new page for signup
void MainWindow::on_signupbutton_clicked()
{
    signup = new signupui(nullptr);
    signup->show();
    connect(signup, &signupui::signupApproved, this, &MainWindow::handleSignupApproved);
}

//open new page for login
void MainWindow::on_loginbutton_clicked()
{
    login = new loginui(nullptr);
    login->show();
    connect(login, &loginui::loginApproved, this, &MainWindow::handleloginApproved);
}



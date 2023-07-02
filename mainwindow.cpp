#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qmessagebox.h>


MainWindow::MainWindow(Client & client,
                       GroupRepository& groupRepo,
                       ChannelRepository& channelRepo,
                       PvRepository& pvRepo,
                       QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    client(client),
    groupRepo(groupRepo),
    channelRepo(channelRepo),
    pvRepo(pvRepo)
{
    ui->setupUi(this);
    if (!client.getToken().isEmpty()) {
        // The client data was successfully read and contains a token, redirect to the logged in page
        loggedin = new loggedinpage(client, groupRepo, channelRepo,pvRepo);
        loggedin->show();
        connect(loggedin, &loggedinpage::logoutbuttonclicked, this, &MainWindow::handleLogoutClicked);
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
void MainWindow::handleloginApproved()
{

    login->close(); // Close the login page
    loggedin = new loggedinpage(client, groupRepo, channelRepo, pvRepo);
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

//for when the program exits
void MainWindow::onMainWindowClosed()
{
    // Called when the MainWindow is closed
    writeAll();
}

void MainWindow::writeAll(){
    qDebug()<<"Caled write all!";
    pvRepo.writeMessages();
    groupRepo.writeMessages();
    channelRepo.writeMessages();
}

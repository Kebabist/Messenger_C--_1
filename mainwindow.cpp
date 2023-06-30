#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qmessagebox.h>


MainWindow::MainWindow(Group &g , GroupRepository &gr , QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) , group(g) , grouprepo(gr)

{
    ui->setupUi(this);

    //connect(loggedin, &loggedinpage::logoutbuttonclicked, this, &MainWindow::handleLogoutClicked);

    // show the main window
    show();
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
    loggedin = new loggedinpage(group , grouprepo , client);
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



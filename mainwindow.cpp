#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
void MainWindow::handleloginApproved()
{
    login->close(); // Close the signup page
    // Show or perform any actions related to the start page
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


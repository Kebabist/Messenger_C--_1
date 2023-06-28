#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "signupui.h"

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

void MainWindow::handleSignupApproved()
{
    signup->close(); // Close the signup page
    // Show or perform any actions related to the start page
}


void MainWindow::on_signupbutton_clicked()
{
    signup = new signupui(nullptr);
    signup->show();
    connect(signup, &signupui::signupApproved, this, &MainWindow::handleSignupApproved);
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qmessagebox.h>
#include <QtCore/QProcess>
#include <QApplication>
#include <QMainWindow>
#include <QProcess>
#include <signal.h>
#include <QCoreApplication>
#include <QDir>
#include "Client/client.h"

MainWindow::MainWindow(Client & client,
                       GroupRepository& groupRepo,
                       ChannelRepository& channelRepo,
                       PvRepository& pvRepo,
                       QWidget *parent)
    : QMainWindow(parent),
    flag(false),
    client(client),
    ui(new Ui::MainWindow),
    groupRepo(groupRepo),
    channelRepo(channelRepo),
    pvRepo(pvRepo)
{
    try{
        ui->setupUi(this);
        loggedin = new loggedinpage(client, groupRepo, channelRepo, pvRepo);
        // Establish connections to the loggedinpage signals and slots
        connect(loggedin, &loggedinpage::logoutbuttonclicked, this, &MainWindow::handleLogoutClicked);
        // connect the loggedinpageClosed() signal to the handleLoggedinpageClosed() slot
        connect(loggedin, &loggedinpage::loggedinpageClosed, this, &MainWindow::handleLoggedinpageClosed);

        // connect the aboutToClose() signal of the QApplication object to a slot in the MainWindow class
        connect(qApp, &QApplication::aboutToQuit, this, &MainWindow::handleAboutToQuit);

        ClientState();
    }catch (...) {
        qDebug() << "Unknown exception caught in mainwindow constructor";
    }
}

MainWindow::~MainWindow()
{   try{
        delete signup;
        delete login;
        delete loggedin;
        delete ui;
    }catch (...) {
        qDebug() << "Unknown exception caught";
    }
}

//handle signup signal
void MainWindow::handleSignupApproved()
{
    signup->close(); // Close the signup page
    // Show or perform any actions related to the start page
}

//handle login signal
void MainWindow::handleloginApproved(Client* loginClient)
{   try{
        login->close(); // Close the login page
        client.setToken(loginClient->getToken());
        client.setPassword(loginClient->getPassword());
        client.setUsername(loginClient->getUsername());
        loggedin->show(); // Show the loggedin page
        qDebug() << "Logged in page shown"; // Debug message
    }catch (...) {
        qDebug() << "Unknown exception caught ";
    }
}

void MainWindow::handleLogoutClicked(){
    try{
        flag =true;
        loggedin->close(); // Close the loggedin page
        // Launch a new instance of the app in a separate process group
        QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
        // Quit the Qt event loop
        qApp->quit();
        // Wait for the event loop to finish processing events
        QCoreApplication::processEvents(QEventLoop::AllEvents, 5000);
        // Fully terminate the current process
        std::exit(0);
    }catch (...) {
    qDebug() << "Unknown exception caught";
    }
}

//open new page for signup
void MainWindow::on_signupbutton_clicked()
{   try{
        signup = new signupui(nullptr);
        signup->show();
        connect(signup, &signupui::signupApproved, this, &MainWindow::handleSignupApproved);
    }catch (...) {
        qDebug() << "Unknown exception caught";
    }
}

//open new page for login
void MainWindow::on_loginbutton_clicked()
{   try{
        login = new loginui(nullptr);
        hide();
        login->show();
        connect(login, &loginui::loginApproved, this, &MainWindow::handleloginApproved);
    }catch (...) {
        qDebug() << "Unknown exception caught";
    }
}

//closes mainwindow when the loggedinpage is closed
void MainWindow::handleLoggedinpageClosed() {
    try{
        if(!flag){
            // Quit the Qt event loop
            qApp->quit();
            // Wait for the event loop to finish processing events
            QCoreApplication::processEvents(QEventLoop::AllEvents, 5000);

            // Fully terminate the current process
            close();
            std::exit(0);
        }
    }catch (...) {
        qDebug() << "Unknown exception caught in handleLoggedinpageClosed()";
    }
}

//Checks the State of the User at Program startup
void MainWindow::ClientState(){
    try{
        client.ReadClient();
        //tries to find client data on disk and see if the user has already logged in or not
        if(client.getToken() != ""){
            hide();
            loggedin->show();
            return;
        }
        else{
            // The client data could not be read or does not contain a token, stay on the main window
            show();
        }
    }catch (...) {
        qDebug() << "Unknown exception caught in mainwindow";
    }
}

//finishes the program background tasks
void MainWindow::handleAboutToQuit()
{
    // call the quit() method of the QApplication object to quit the application
    qApp->quit();
}

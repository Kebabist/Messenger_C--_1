#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "signupui.h"
#include "loginui.h"
#include "loggedinpage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //buttons
    void on_signupbutton_clicked();
    void on_loginbutton_clicked();

    //handle the pages signals
    void handleSignupApproved();
    void handleloginApproved();


private:
    Ui::MainWindow *ui;
    //create signup page object
    signupui *signup;
    //create login page object
    loginui *login;
    //create loggedinpage object
    loggedinpage *loggedin;
};
#endif // MAINWINDOW_H

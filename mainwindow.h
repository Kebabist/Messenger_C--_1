#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "signupui.h"
#include "ui_signup.h"

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
    void on_signupbutton_clicked();
    void handleSignupApproved();

private:
    Ui::MainWindow *ui;
    signupui *signup;
};
#endif // MAINWINDOW_H

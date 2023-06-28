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


void MainWindow::on_signupbutton_clicked()
{
    signupui *signup = new signupui(nullptr); // Pass nullptr as parent widget parameter
    signup->show();
}

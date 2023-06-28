#include "loggedinpage.h"
#include "ui_loggedinpage.h"

loggedinpage::loggedinpage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loggedinpage)
{
    ui->setupUi(this);
}

loggedinpage::~loggedinpage()
{
    delete ui;
}

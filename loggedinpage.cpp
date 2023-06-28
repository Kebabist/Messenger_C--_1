#include "loggedinpage.h"
#include "ui_loggedinpage.h"

loggedinpage::loggedinpage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loggedinpage)
{
    ui->setupUi(this);
    connect(ui->toggleview, SIGNAL(clicked(bool)), this, SLOT(onToggleviewClicked(bool)));
    ui->dockWidget->setTitleBarWidget(ui->widget_3);
}

loggedinpage::~loggedinpage()
{
    delete ui;
}

void loggedinpage::on_toggleview_clicked(bool checked)
{
    ui->dockWidget->setVisible(checked);
}


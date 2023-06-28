#include "signupui.h"
#include "ui_signupui.h"

signupui::signupui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::signupui)
{
    ui->setupUi(this);
}

signupui::~signupui()
{
    delete ui;
}

void signupui::on_submitbutton_clicked()
{

}


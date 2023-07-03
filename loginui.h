#ifndef LOGINUI_H
#define LOGINUI_H

#include <QWidget>
#include <QShortcut>
#include "client.h"

namespace Ui {
class loginui;
}

class loginui : public QWidget
{
    Q_OBJECT

public:
    explicit loginui(QWidget *parent = nullptr);
    ~loginui();

private slots:
    //submit button clicl
    void on_submitbutton_clicked();
signals:
//correct credentials signal (sent to mainwindow)
    void loginApproved(Client *loginclient);
private:
    Ui::loginui *ui;
};

#endif // LOGINUI_H

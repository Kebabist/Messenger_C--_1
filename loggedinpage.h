#ifndef LOGGEDINPAGE_H
#define LOGGEDINPAGE_H

#include <QWidget>
#include "client.h"

namespace Ui {
class loggedinpage;
}

class loggedinpage : public QWidget
{
    Q_OBJECT

public:
    explicit loggedinpage(Client &client , QWidget *parent = nullptr);
    ~loggedinpage();

private slots:
    void on_toggleview_clicked(bool checked);

    void on_logoutbutton_clicked();

signals:
    //emit when the button is clicked
    void logoutbuttonclicked();

private:
    Ui::loggedinpage *ui;
    Client cl;
};

#endif // LOGGEDINPAGE_H

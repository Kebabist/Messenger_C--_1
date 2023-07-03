#ifndef SIGNUPUI_H
#define SIGNUPUI_H

#include <QWidget>
#include <QShortcut>

namespace Ui {
class signupui;
}

class signupui : public QWidget
{
    Q_OBJECT

public:
    explicit signupui(QWidget *parent = nullptr);
    ~signupui();

private slots:
    void on_submitbutton_clicked();
signals:
    //correct credentials signal (sent to mainwindow)
    void signupApproved();
private:
    Ui::signupui *ui;
};

#endif // SIGNUPUI_H

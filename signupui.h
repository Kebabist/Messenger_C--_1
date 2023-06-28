#ifndef SIGNUPUI_H
#define SIGNUPUI_H

#include <QWidget>

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

private:
    Ui::signupui *ui;
};

#endif // SIGNUPUI_H

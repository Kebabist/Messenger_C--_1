#ifndef LOGGEDINPAGE_H
#define LOGGEDINPAGE_H

#include <QWidget>

namespace Ui {
class loggedinpage;
}

class loggedinpage : public QWidget
{
    Q_OBJECT

public:
    explicit loggedinpage(QWidget *parent = nullptr);
    ~loggedinpage();

private slots:
    void on_toggleview_clicked(bool checked);

private:
    Ui::loggedinpage *ui;
};

#endif // LOGGEDINPAGE_H

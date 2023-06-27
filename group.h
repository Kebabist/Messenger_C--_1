#ifndef GROUP_H
#define GROUP_H
#include <QWidget>
#include "client.h"
#include "urlmaker.h"
#include "httphandler.h"

namespace Ui {
class group;
}

class group : public QWidget
{
    Q_OBJECT
    QString group_name;
    QString group_title;
public:
    explicit group(QWidget *parent = nullptr);
    group(QString , QString);
    void create(Client &c);
    void getmessgae();
    void sendmessage();
    void getlist(Client &c);
    void join(Client &c);
    ~group();

private:
    Ui::group *ui;
};

#endif // GROUP_H

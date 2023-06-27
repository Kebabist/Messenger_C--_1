#ifndef GROUP_H
#define GROUP_H
#include <QWidget>
#include "client.h"
#include "urlmaker.h"
#include "user.h"
#include "httphandler.h"

namespace Ui {
class group;
}

class group : public virtual QWidget, public user
{
    Q_OBJECT
    QString group_name;
    QString group_title;
public:
    explicit group(QWidget *parent = nullptr);
    group(QString , QString);
    void create(Client &c);
    ~group();

private:
    Ui::group *ui;
};

#endif // GROUP_H

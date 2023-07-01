#ifndef LOGGEDINPAGE_H
#define LOGGEDINPAGE_H

#include <QWidget>
#include "client.h"
#include <qlistwidget.h>
#include "grouprepository.h"
#include "channelrepository.h"
#include "pvrepository.h"

namespace Ui {
class loggedinpage;
}

class loggedinpage : public QWidget
{
    Q_OBJECT

public:
    explicit loggedinpage(const std::vector<std::unique_ptr<DTO>>& groupList,
                          const std::vector<std::unique_ptr<DTO>>& pvList,
                          const std::vector<std::unique_ptr<DTO>>& channelList,Client &client , QWidget *parent = nullptr);
    void addtopage(const std::vector<std::unique_ptr<DTO>>& groupList);
    ~loggedinpage();

private slots:
    void on_toggleview_clicked(bool checked);
    void handleListItemClicked(QListWidgetItem* item);
    void on_logoutbutton_clicked();

signals:
    //emit when the button is clicked
    void logoutbuttonclicked();

private:
    Ui::loggedinpage *ui;
    Client cl;
    const std::vector<std::unique_ptr<DTO>>& pvList;
    const std::vector<std::unique_ptr<DTO>>& groupList;
    const std::vector<std::unique_ptr<DTO>>& channelList;
    QMultiMap<QString, QPair<QString , QString>> group_messages;
    QMultiMap<QString, QPair<QString , QString>> channel_messages;
    QMultiMap<QString, QPair<QString , QString>> pv_messages;
};

#endif // LOGGEDINPAGE_H

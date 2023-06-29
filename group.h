#ifndef GROUP_H
#define GROUP_H

#include <QWidget>
#include <QString>
#include <qmap.h>

//namespace Ui {
//class Group;
//}

//Group class that holds necessary Group data
class Group : public QWidget
{
    Q_OBJECT

public:
    //    explicit Group(QWidget *parent = nullptr);
    Group();
    Group(QString title , const QString& name );
    Group(const Group& other);
    Group& operator=(const Group& other);
    ~Group();

    //getter
    QString getGrouptitle() const;
    QString getGroupname() const;
    const QMultiMap<QString, QPair<QString, QString>> &getGroupmessages() const;

    //overloading
    bool operator==(const Group& other) const;


    //setter
    void setGroupmessages(QString  , QString   , QString );

private:
    QString Group_title;
    QString Group_name;
    QMultiMap<QString, QPair<QString, QString>> Group_messages;
    //    Ui::Group *ui;
};



#endif // GROUP_H

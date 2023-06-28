#ifndef GROUP_H
#define GROUP_H

#include <QWidget>
#include <QString>
#include <QList>

//namespace Ui {
//class Group;
//}

//Group class that holds necessary Group data
class Group : public QWidget
{
    Q_OBJECT

public:
//    explicit Group(QWidget *parent = nullptr);
    Group(int id = 0, const QString& name = "", const QMap<QString, QString>& messages = {});
    Group(const Group& other);
    Group& operator=(const Group& other);
    ~Group();

    //getter
    int getGroupid() const;
    QString getGroupname() const;
    QMap<QString, QString> getGroupmessages() const;


private:
    int Group_id;
    QString Group_name;
    QMap<QString, QString> Group_messages;
//    Ui::Group *ui;
};



#endif // GROUP_H
#ifndef GROUP_H
#define GROUP_H

#include <QWidget>
#include <QString>
#include <QList>

namespace Ui {
class Group;
}

//Group class that holds necessary Group data
class Group : public QWidget
{
    Q_OBJECT

public:
    explicit Group(QWidget *parent = nullptr);
    Group();
    Group(int id, const QString& name, const QMap<QString, QString>& messages);
    ~Group();

    //getter
    QString getGroupname() const;
    int getGroupid() const;
    QMap<QString, QString> getGroupmessages() const;


private:
    int Group_id;
    QString Group_name;
    QMap<QString, QString> Group_messages;
    Ui::Group *ui;
};



#endif // GROUP_H

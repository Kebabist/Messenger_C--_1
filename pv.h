#ifndef PV_H
#define PV_H


#include <QWidget>
#include <QString>
#include <qmap.h>

//Pv class that holds necessary Pv data
class Pv : public QWidget
{
    Q_OBJECT

public:
    //    explicit Pv(QWidget *parent = nullptr);
    Pv();
    Pv(const QString& name );
    Pv(const Pv& other);
    Pv& operator=(const Pv& other);
    ~Pv();

    //getter
    QString getPvname() const;
    const QMultiMap<QString, QPair<QString, QString>> &getPvmessages() const;

    //overloading
    bool operator==(const Pv& other) const;


    //setter
    void setPvmessages(QString  , QString   , QString );

private:
    QString Pv_name;
    QMultiMap<QString, QPair<QString, QString>> Pv_messages;
};



#endif // PV_H

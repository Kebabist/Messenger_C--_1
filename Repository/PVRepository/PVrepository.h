#ifndef PVREPOSITORY_H
#define PVREPOSITORY_H

#include <QWidget>
#include <QList>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDir>
#include <QFile>
#include <QByteArray>
#include <QStandardPaths>
#include <vector>
#include <Repository/Repository/repository.h>
#include "DTO/PV/pv.h"

class PvRepository : public Repository
{

public:
    PvRepository();
    PvRepository(const PvRepository& other);
    ~PvRepository();

    QString create(QString token, QString name) override;
    QString join(QString token, QString name) override;
    void getList(QString token) override;
    QString sendMessage(QString token, QString name, QString message) override;
    const QString findLatestDate(QString name) override;
    void getChats(QString token, QString name, QString date= "") override;
    void removeDir() override;
    void writeMessages() override;
    void readMessages() override;
    void display() override;

};


#endif // PvREPOSITORY_H

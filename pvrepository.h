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
#include "pv.h"
#include "repository.h"

class PvRepository : public Repository
{

public:
    PvRepository();
    PvRepository(const PvRepository& other);
    ~PvRepository();

    void create(QString token, QString name) override;
    void join(QString token, QString name) override;
    void getList(QString token) override;
    void sendMessage(QString token, QString name, QString message) override;
    const QString findLatestDate(QString name) override;
    void getChats(QString token, QString name, QString date= "") override;
    void removeDir() override;
    void writeMessages() override;
    void readMessages() override;
    void display() override;

};


#endif // PvREPOSITORY_H

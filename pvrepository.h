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
#include "PV.h"
#include "httpHandler.h"
#include "urlmaker.h"
#include "client.h"

class PvRepository : public QWidget
{
    Q_OBJECT

public:
    PvRepository();
    ~PvRepository();

    void getPvlist(QString token);
    void sendmessagePv(QString token, QString pvName , QString message);
    const QString findLatestdate(QString pvName) const;
    void getPvchats(QString token , QString pvName , QString date);
    void RemovePvsDir();
    void WritePvsmessages();
    void ReadPvsmessages();
    void display();

    //setter function
    void setPvsList(const std::unique_ptr<Pv> newpv);

    //getter function
    const std::vector<std::unique_ptr<Pv>>& getPv_list() const;

private:
    HttpHandler http;
    urlmaker urlMaker;
    std::vector<std::unique_ptr<Pv>> Pvs_list;
};
#endif // PvREPOSITORY_H

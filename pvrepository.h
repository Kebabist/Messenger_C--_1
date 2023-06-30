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
#include "pv.h"
#include "httpHandler.h"
#include "urlmaker.h"
#include "client.h"

class PvRepository : public QWidget
{
    Q_OBJECT

public:
    PvRepository();
    ~PvRepository();

    void getPvlist(Client &c);
    void getPvchats(Client &c , QString dst , QString date);
    void sendmessagePv(QString desiredpv , QString text , Client &c);
    void display();
    void RemovePvsDir();
    void WritePvsmessages();
    void ReadPvsmessages();

    //setter function
    void setPvList(const Pv& newPv);

    //getter function
    const QList<Pv>& getPv_list() const;


private:
    HttpHandler http;
    urlmaker urlMaker;
    QList<Pv> Pvs_list;
};

#endif // PvREPOSITORY_H

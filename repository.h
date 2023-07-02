#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QWidget>
#include <QList>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDir>
#include <QFile>
#include <QByteArray>
#include <QStandardPaths>
#include <vector>
#include "httpHandler.h"
#include "urlmaker.h"
#include "dto.h"

class Repository
{
public:
    Repository();
    virtual ~Repository();

    // Common methods
    virtual QString create(QString token, QString name) = 0;
    virtual QString join(QString token, QString name) = 0;
    virtual void getList(QString token) = 0;
    virtual QString sendMessage(QString token, QString name, QString message) = 0;
    virtual const QString findLatestDate(QString name) = 0;
    virtual void getChats(QString token, QString name, QString date) = 0;
    virtual void removeDir() = 0;
    virtual void writeMessages() = 0;
    virtual void readMessages() = 0;
    virtual void display() = 0;

    // Setter
    void setList(std::unique_ptr<DTO> newDTO);

    // Getter
    const std::vector<std::unique_ptr<DTO>>& get_List() const;

protected:
    HttpHandler http;
    urlmaker urlMaker;
    std::vector<std::unique_ptr<DTO>> list;
};

#endif // REPOSITORY_H

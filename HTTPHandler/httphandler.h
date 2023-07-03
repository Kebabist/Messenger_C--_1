#ifndef HTTPHANDLER_H
#define HTTPHANDLER_H

#include <QCoreApplication>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

class HttpHandler : public QObject
{
    Q_OBJECT
private:
    QNetworkAccessManager manager;

public:
    explicit HttpHandler(QObject *parent = nullptr) : QObject(parent), manager(this) {}

public slots:
    QPair<QJsonObject, bool> makeRequest(const QString &);
};

#endif // HTTPHANDLER_H

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
public:
    explicit HttpHandler(QObject *parent = nullptr);
    void post(const QString& url, const QByteArray& data);
    void put(const QString& url, const QByteArray& data);
    void deleteResource(const QString& url);
signals:
    void requestFinished(const QByteArray& data);

private slots:
    void onReplyFinished(QNetworkReply* reply);

public slots:
    QPair<QJsonObject, bool> makeRequest(const QString &)
        ;
private:
    QNetworkAccessManager manager;
};

#endif // HTTPHANDLER_H

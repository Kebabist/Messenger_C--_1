#include "httphandler.h"

void HttpHandler::makeRequest(const QString &urlString)
    {
        QUrl url(urlString);
        QNetworkReply *reply = manager.get(QNetworkRequest(url)); // Send GET request

        connect(reply, &QNetworkReply::finished, this, [=]() {
            if (reply->error() == QNetworkReply::NoError) {
                // If the request was successful, read the response
                QByteArray data = reply->readAll();
                qDebug() << "Response:" << data;
                QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
                QJsonObject jsonObj = jsonDoc.object();

                double userId = jsonObj.value("userId").toDouble();
                QString title = jsonObj.value("title").toString();
                qDebug() << "User ID:" << userId << ", title: " << title << Qt::endl;
            } else {
                // If there was an error, display the error message
                qDebug() << "Error:" << reply->errorString();
            }

            // Cleanup the reply object
            reply->deleteLater();
        });
    }

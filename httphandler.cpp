#include "httphandler.h"

////handles the http requests
//QPair<QJsonObject, bool> HttpHandler::makeRequest(const QString &urlString)
//    {
//        QUrl url(urlString);
//        QNetworkReply *reply = manager.get(QNetworkRequest(url)); // Send GET request

//        QJsonObject jsonObj;
//        bool success = false;

//        QEventLoop loop;
//        connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
//        loop.exec(); // Block until the request is finished
//            if (reply->error() == QNetworkReply::NoError) {
//                // If the request was successful, read the response
//                QByteArray data = reply->readAll();

//                QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
//                jsonObj = jsonDoc.object();
//                // Check if the JSON object contains the expected keys
//                if (jsonObj.contains("message") && jsonObj.contains("code")) {
//                    success = true;
//                }
//            }
//            else {
//                // If there was an error, display the error message
//                qDebug() << "Error:" << reply->errorString();
//            }

//            // Cleanup the reply object
//            reply->deleteLater();
//            return qMakePair(jsonObj, success);
//    }

#include "exceptionhandler.h"
QPair<QJsonObject, bool> HttpHandler::makeRequest(const QString &urlString)
{
    QUrl url(urlString);
    QNetworkReply *reply = manager.get(QNetworkRequest(url)); // Send GET request

    QJsonObject jsonObj;
    bool success = false;

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec(); // Block until the request is finished

    if (reply->error() == QNetworkReply::NoError) {
        // If the request was successful, read the response
        QByteArray data = reply->readAll();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        jsonObj = jsonDoc.object();
        // Check if the JSON object contains the expected keys
        if (jsonObj.contains("message") && jsonObj.contains("code")) {
            success = true;
            // Check if the code indicates a failure
            if (jsonObj.value("code").toString() != "200") {
                QString message = jsonObj.value("message").toString();
                QString code = jsonObj.value("code").toString();
                // Throw an exception with the error message and code
                throw HttpHandlerException(message, code);
            }
        }
    } else {
        // If there was an error, display the error message
        qDebug() << "Error:" << reply->errorString();
    }

    // Cleanup the reply object
    reply->deleteLater();
    return qMakePair(jsonObj, success);
}

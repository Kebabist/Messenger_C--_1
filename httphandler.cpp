#include "httphandler.h"
#include "exceptionhandler.h"

//handles server Queries
//QPair<QJsonObject, bool> HttpHandler::makeRequest(const QString &urlString)
//{
//    QUrl url(urlString);
//    QNetworkReply *reply = manager.get(QNetworkRequest(url)); // Send GET request

//    QJsonObject jsonObj;
//    bool success = false;

//    QEventLoop loop;
//    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
//    loop.exec(); // Block until the request is finished

//    if (reply->error() == QNetworkReply::NoError) {
//        // If the request was successful, read the response
//        QByteArray data = reply->readAll();

//        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
//        jsonObj = jsonDoc.object();
//        // Check if the JSON object contains the expected keys
//        if (jsonObj.contains("message") && jsonObj.contains("code")) {
//            success = true;
//            // Check if the code indicates a failure
//            if (jsonObj.value("code").toString() != "200") {
//                QString message = jsonObj.value("message").toString();
//                QString code = jsonObj.value("code").toString();
//                // Throw an exception with the error message and code
//                throw ExceptionHandler(message, code);
//            }
//        }
//    } else {
//        // If there was an error, display the error message
//        qDebug() << "Error:" << reply->errorString();
//    }

//    // Cleanup the reply object
//    reply->deleteLater();
//    return qMakePair(jsonObj, success);
//}
QPair<QJsonObject, bool> HttpHandler::makeRequest(const QString &urlString) {
    try {
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
            }
        } else {
            // If there was an error, throw an exception
            QString message = reply->errorString();
            QString code = "NETWORK_ERROR";
            throw ExceptionHandler(message, code);
        }

        // Cleanup the reply object
        reply->deleteLater();
        return qMakePair(jsonObj, success);
    }
    catch (const ExceptionHandler& e) {
        // Handle the exception
        qDebug() << "Error: " << e.message() << " (" << e.code() << ")";
        return qMakePair(QJsonObject(), false);
        //re-throw here if it's needed to handle the exception further up the call stack
        // throw;
    }
    catch (...) {
        // Handle any other exceptions
        qDebug() << "Unknown Network error occurred";
    }
}

#ifndef URLMAKER_H
#define URLMAKER_H

#include <QString>

//creates the required urls
class urlmaker
{
private:
    QString command;
    QString token;
    QString arguments;
public:
    urlmaker();
    urlmaker(QString , QString , QString);
    urlmaker(QString , QString);
    const QString generate();
};

#endif // URLMAKER_H

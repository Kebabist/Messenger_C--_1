#ifndef URLMAKER_H
#define URLMAKER_H
#include <QString>

class urlmaker
{
    QString command;
    QString token;
    QString arguments;
public:
    urlmaker(QString , QString , QString);
    QString generate();
};

#endif // URLMAKER_H

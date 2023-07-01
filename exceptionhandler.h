#ifndef EXCEPTIONHANDLER_H
#define EXCEPTIONHANDLER_H

#include <QException>
#include <QString>

//handles exception during program runtime
class ExceptionHandler : public QException
{
public:
    ExceptionHandler(const QString &message, const QString &code);
    void raise() const override;
    QException *clone() const override;

    QString message() const;
    QString code() const;

private:
    QString m_message;
    QString m_code;
};


#endif // EXCEPTIONHANDLER_H

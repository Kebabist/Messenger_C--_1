#ifndef EXCEPTIONHANDLER_H
#define EXCEPTIONHANDLER_H

#include <QWidget>
#include <QException>
#include <QString>

//namespace Ui {
//class Exceptionhandler;
//}

//class Exceptionhandler : public QException
//{
//    Q_OBJECT

//public:
//    explicit Exceptionhandler(QWidget *parent = nullptr);
//    void raise() const override { throw *this; }
//    MyException *clone() const override { return new MyException(*this); }
//    ~Exceptionhandler();

//private:
//    Ui::Exceptionhandler *ui;
//};

//handles exception during program runtime
class HttpHandlerException : public QException
{
public:
    HttpHandlerException(const QString &message, const QString &code);
    void raise() const override;
    QException *clone() const override;

    QString message() const;
    QString code() const;

private:
    QString m_message;
    QString m_code;
};


#endif // EXCEPTIONHANDLER_H

//#include "exceptionhandler.h"
//#include "ui_exceptionhandler.h"

//Exceptionhandler::Exceptionhandler(QWidget *parent) :
//    QWidget(parent),
//    ui(new Ui::Exceptionhandler)
//{
//    ui->setupUi(this);
//}

//Exceptionhandler::~Exceptionhandler()
//{
//    delete ui;
//}

#include "exceptionhandler.h"

// Constructor that takes an error message and an error code
HttpHandlerException::HttpHandlerException(const QString &message, const QString &code)
    : m_message(message), m_code(code)
{

}

// Function that throws the exception
void HttpHandlerException::raise() const
{
    throw *this;
}

// Function that creates a copy of the exception
QException *HttpHandlerException::clone() const
{
    return new HttpHandlerException(m_message, m_code);
}

// Function that creates a copy of the exception
QString HttpHandlerException::message() const
{
    return m_message;
}

 // Function that returns the error code
QString HttpHandlerException::code() const
{
    return m_code;
}

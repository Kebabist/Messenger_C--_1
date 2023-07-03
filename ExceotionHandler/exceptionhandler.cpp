#include "exceptionhandler.h"

// Constructor that takes an error message and an error code
ExceptionHandler::ExceptionHandler(const QString &message, const QString &code)
    : m_message(message), m_code(code)
{}

// Function that throws the exception
void ExceptionHandler::raise() const
{
    throw *this;
}

// Function that creates a copy of the exception
QException *ExceptionHandler::clone() const
{
    return new ExceptionHandler(m_message, m_code);
}

// Function that creates a copy of the exception
QString ExceptionHandler::message() const
{
    return m_message;
}

 // Function that returns the error code
QString ExceptionHandler::code() const
{
    return m_code;
}

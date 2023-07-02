#include "dto.h"


//default constructor
DTO::DTO()
{}

//Constructor
DTO::DTO(QString name, QString title) : name(name) , title(title)
{}

//copy constructor
DTO::DTO(const DTO& other)
    : name(other.name), title(other.title), messages(other.messages)
{}

//Destructor
DTO::~DTO()
{}

//copy assignment operator
DTO& DTO::operator=(const DTO& other)
{
    if (this != &other) {
        name = other.name;
        title = other.title;
        messages = other.messages;
    }
    return *this;
}

//Getters
const QString DTO::getName() const
{
    return name;
}

const QString DTO::getTitle() const
{
    return title;
}

const QMultiMap<QString, QPair<QString, QString>> &DTO::getMessages() const
{
    return messages;
}

//Setters
void DTO::setMessage(QString src, QString message, QString date)
{
    if (!messages.isEmpty() && messages.lastKey() == date &&
        messages.last().first == src && messages.last().second == message) {
        // Last key, src, and message are the same as the new values, do nothing
        return;
    }
    // Add a new key-value pair to the map
    messages.insert(date, QPair<QString, QString>(src, message));
}

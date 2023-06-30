#include "pv.h"

Pv::Pv()
{}

//Pv class Constructor
Pv::Pv(const QString& name)
    :  Pv_name(name)
{}

//copy constructor
Pv::Pv(const Pv& other)
    :  Pv_name(other.Pv_name), Pv_messages(other.Pv_messages)
{}

//setter
void Pv::setPvmessages(QString src , QString  message , QString date){
    Pv_messages.insert(date, QPair<QString, QString>(src, message));
}


//overloading
bool Pv::operator==(const Pv& other) const {
    return Pv_name == other.Pv_name;
}

//copy assignment operator
Pv& Pv::operator=(const Pv& other)
{
    if (this != &other) {
        Pv_name = other.Pv_name;
        Pv_messages = other.Pv_messages;
    }
    return *this;
}

Pv::~Pv()
{}

//getter functions
QString Pv::getPvname() const{
    return Pv_name;
}


const QMultiMap<QString, QPair<QString, QString>>& Pv::getPvmessages() const  {
    return Pv_messages;
}

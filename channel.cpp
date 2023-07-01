#include "channel.h"

//default constructor
Channel::Channel()
{}

//Destructor
Channel::~Channel()
{}

//Channel class Constructor
Channel::Channel(QString name, QString title) : DTO(name, title)
{}

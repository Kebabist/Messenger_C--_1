#include "group.h"

//default constructor
Group::Group()
{}

//Destructor
Group::~Group()
{}

//Group class Constructor
Group::Group(QString name, QString title) : DTO(name, title)
{}

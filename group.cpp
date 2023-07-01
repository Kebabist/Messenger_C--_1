#include "group.h"
//#include "Ui_group.h"

//default constructor
Group::Group()
{}

//Destructor
Group::~Group()
{}

//Group class Constructor
Group::Group(QString name, QString title = "G") : DTO(name, title)
{}

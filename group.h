#ifndef GROUP_H
#define GROUP_H

#include "dto.h"

//Group class that holds necessary Group data
class Group : public DTO
{
public:
    Group();
    Group(QString name , QString title);
    ~Group();
};



#endif // GROUP_H

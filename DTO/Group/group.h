#ifndef GROUP_H
#define GROUP_H

#include "DTO/DTOParent/dto.h"

class Group : public DTO
{
public:
    Group();
    Group(QString name , QString title="G");
    ~Group();
};

#endif // GROUP_H

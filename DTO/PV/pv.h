#ifndef PV_H
#define PV_H

#include "DTO/DTOParent/dto.h"

class Pv: public DTO
{
public:
    Pv();
    Pv(QString name , QString title="P");
    ~Pv();
};


#endif // PV_H

#ifndef CHANNEL_H
#define CHANNEL_H

#include "DTO/DTOParent/dto.h"

class Channel: public DTO
{
public:
    Channel();
    Channel(QString name , QString title="C");
    ~Channel();
};

#endif // CHANNEL_H

#ifndef CHANNEL_H
#define CHANNEL_H

#include "dto.h"

class Channel: public DTO
{
public:
    Channel();
    Channel(QString name , QString title="C");
    ~Channel();
};

#endif // CHANNEL_H

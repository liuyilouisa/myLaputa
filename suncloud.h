#ifndef SUNCLOUD_H
#define SUNCLOUD_H

#include "cloud.h"

class SunCloud : public Cloud
{
public:
    SunCloud();
    void advance(int phase) override;
};

#endif // SUNCLOUD_H

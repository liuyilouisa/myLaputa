#ifndef BLOCKCLOUD_H
#define BLOCKCLOUD_H

#include "cloud.h"

class BlockCloud : public Cloud
{
public:
    BlockCloud();
    void advance(int phase) override;
};

#endif // BLOCKCLOUD_H

#ifndef SNOWCLOUD_H
#define SNOWCLOUD_H

#include "cloud.h"
#include "plane.h"
#include "drop.h"

class SnowCloud : public Cloud
{
public:
    SnowCloud();
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
};

#endif // SNOWCLOUD_H

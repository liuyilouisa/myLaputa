#ifndef RAINCLOUD_H
#define RAINCLOUD_H

#include "cloud.h"

class RainCloud : public Cloud
{
public:
    RainCloud();
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;

};

#endif // RAINCLOUD_H

#ifndef LIGHTENINGCLOUD_H
#define LIGHTENINGCLOUD_H

#include "cloud.h"
#include "plane.h"

class LighteningCloud : public Cloud
{
public:
    LighteningCloud();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
private:
    bool throwLightening;
    int lighteningTime;
};

#endif // LIGHTENINGCLOUD_H

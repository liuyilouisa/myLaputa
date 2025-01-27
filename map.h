#ifndef MAP_H
#define MAP_H

#include "other.h"
#include "cloud.h"
#include "shop.h"
#include <QGraphicsSceneDragDropEvent>

class Map : public Other
{
public:
    Map(Shop *s);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) override;
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;
private:
    bool dragOver;
    Shop *shop;
};

#endif // MAP_H

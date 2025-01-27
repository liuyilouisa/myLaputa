#ifndef SHOP_H
#define SHOP_H

#include "other.h"
#include "card.h"

class Shop : public Other
{
public:
    int sun;
    Shop();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void advance(int phase) override;
    void addCloud(QString s, QPointF pos);
    void addSunValue(int value);
private:
    int counter;
    int time;
    std::vector<Card*> cards;
};

#endif // SHOP_H

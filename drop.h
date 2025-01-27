#ifndef DROP_H
#define DROP_H

#include "other.h"

class Drop : public Other
{
public:
    Drop(int attack = 0, bool flag = false);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    void advance(int phase) override;
private:
    bool snow;
    int atk;
    qreal speed;
};

#endif // DROP_H

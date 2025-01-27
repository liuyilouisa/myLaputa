#ifndef SUN_H
#define SUN_H

#include <QGraphicsItem>

class Sun : public QGraphicsItem
{
public:
    Sun();
    enum { Type = UserType + 4};
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void advance(int phase) override;
    int type() const override;
private:
    QPointF dest;
    qreal speed;
    bool collected;
};

#endif // SUN_H

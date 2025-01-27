#ifndef PLANE_H
#define PLANE_H

#include <QGraphicsItem>
#include <QGraphicsItem>
#include <QPainter>
#include <QMovie>

class Plane : public QGraphicsItem
{
public:
    int hp;
    int atk;
    int state;
    QString name;
    qreal speed;
    enum { Type = UserType + 2};
    Plane();
    QRectF boundingRect() const override;
    void advance(int phase) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    int type() const override;
};

#endif // PLANE_H

#ifndef CLOUD_H
#define CLOUD_H

#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QMovie>

class Cloud : public QGraphicsItem
{
public:
    QString name;
    double lifetime;
    int hp;
    int state;
    int product;
    enum { Type = UserType + 1};
    Cloud();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    int type() const override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;

protected:
    int atk;
    int counter;
    int time;
    int cost;
};

#endif // CLOUD_H

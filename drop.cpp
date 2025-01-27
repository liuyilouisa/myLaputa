#include "drop.h"
#include "plane.h"
#include "audiomanager.h"

Drop::Drop(int attack, bool flag){
    snow = flag;
    atk = attack;
    speed = 360.0 * 33 / 1000;
}

QRectF Drop::boundingRect() const{
    return QRectF(-14,-14,28,28);
}

void Drop::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawPixmap(QRect(-12, -28, 24, 24), QPixmap(snow ? ":/res/SnowFlake.png" : ":/res/Raindrop.png"));
}

bool Drop::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type() == Plane::Type && qFuzzyCompare(other->x(), x()) && qAbs(other->y() - y()) < 15;
}

void Drop::advance(int phase)
{
    if (!phase)
        return;
    update();
    QList<QGraphicsItem *> items = collidingItems();
    if (!items.isEmpty()){
        Plane *plane = qgraphicsitem_cast<Plane*>(items[0]);
        plane->hp -= atk;
        if (snow && plane->speed > 0.5){
            plane->speed/=2;
        }
        if (!snow)
            AudioManager::instance()->playSound("qrc:/res/drop.mp3");
        delete this;
        return;
    }
    setY(y() + speed);
    if (y() > 780)
        delete this;
}



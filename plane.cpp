#include "plane.h"
#include "cloud.h"

Plane::Plane() {
    hp = atk = state = 0;
    speed = .0;
}

QRectF Plane::boundingRect() const{
    return QRectF(-45,-45,90,90);
}

void Plane::advance(int phase)
{
    if (!phase)
        return;
    update();
    if (hp <= 0){
        speed = -15;
        if (y() >= 800){
            delete this;
            return;
        }
    }
    else{
        QList<QGraphicsItem *> items = collidingItems();
        if (!items.isEmpty()){
            Cloud *cloud = qgraphicsitem_cast<Cloud *>(items[0]);
            cloud->hp -= atk;
            // if (state != 1)
            // {
            //     state = 1;
            // }
            return;
        }
    }
    // if (state){
    //     state = 0;
    // }
    setY(y() - speed);
}

void Plane::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(QRect(-50,-50,100,100), QPixmap(":/res/" + name + ".png"));
}

bool Plane::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type() == Cloud::Type && qFuzzyCompare(other->x(), x()) && y() - other->y() < 30 && y() - other->y() > 0;
}

int Plane::type() const
{
    return Type;
}

#include "snowcloud.h"

SnowCloud::SnowCloud() {
    name = "SnowCloud";
    atk = 50;
    hp = lifetime = 2500;
    time = int(1.4 * 1000 / 33);
}

void SnowCloud::advance(int phase){
    if (!phase)
        return;
    update();
    hp -= 1;
    if (hp <= 0)
        delete this;
    else if (++counter >= time)
    {
        counter = 0;
        if (!collidingItems().isEmpty()){
            hp -= 1;
            Drop *drop = new Drop(atk, true);
            drop->setX(x());
            drop->setY(y() + 32);
            scene()->addItem(drop);
            return;
        }
    }
}

bool SnowCloud::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type() == Plane::Type && qFuzzyCompare(other->x(), x());
}

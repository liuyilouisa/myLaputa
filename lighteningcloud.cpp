#include "lighteningcloud.h"
#include "audiomanager.h"

LighteningCloud::LighteningCloud() {
    name = "LighteningCloud";
    atk = 75;
    hp = lifetime = 1000;
    time = int(1.4 * 1000 / 33);
    throwLightening = false;
    lighteningTime = 0;
}

void LighteningCloud::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setOpacity((double)hp/lifetime);
    painter->drawPixmap(QRect(-50,-50,100,100), QPixmap(":/res/" + name + ".png"));
    if (throwLightening){
        if (lighteningTime == 0) {
            AudioManager::instance()->playSound("qrc:/res/thunder.mp3");
        }
        lighteningTime++;
        if (lighteningTime % 2){
            painter->setBrush(QColor(255, 255, 0));
            painter->setPen(Qt::NoPen);
            painter->drawRect(QRect(-5,10,10,600));
        }
        if (lighteningTime >= 5){
            throwLightening = false;
            lighteningTime = 0;
        }
    }
}

void LighteningCloud::advance(int phase){
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
            QList<QGraphicsItem *> items = collidingItems();
            if (!items.isEmpty()){
                foreach (QGraphicsItem *item, items){
                    if (item->type() == Plane::Type) {
                        Plane *plane = qgraphicsitem_cast<Plane*>(item);
                        if (plane) {
                            hp -= 1;
                            plane->hp -= atk;
                            throwLightening = true;
                        }
                    }
                }
            }
        }
    }
}

bool LighteningCloud::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type() == Plane::Type && qFuzzyCompare(other->x(), x()) && qAbs(other->y() - y()) < 500;
}

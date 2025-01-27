#include "cloud.h"
#include "plane.h"
#include "other.h"
#include "shop.h"
#include "audiomanager.h"

Cloud::Cloud() {
    lifetime = atk = counter = state = time = 0;
    product = 10;
    cost = 100;
}

QRectF Cloud::boundingRect() const{
    return QRectF(-45,-25,90,50);
}

void Cloud::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setOpacity((double)hp/lifetime);
    painter->drawPixmap(QRect(-50,-50,100,100), QPixmap(":/res/" + name + ".png"));
}

bool Cloud::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type() == Plane::Type && qFuzzyCompare(other->x(), x()) && abs(other->y() - y()) < 30;
}

int Cloud::type() const
{
    return Type;
}

void Cloud::contextMenuEvent(QGraphicsSceneContextMenuEvent* event){
    Q_UNUSED(event)
    QGraphicsScene* scene = this->scene();
    if (!scene) return;
    QList<QGraphicsItem*> items = scene->items();
    for (QGraphicsItem* item : items) {
        if (item->type() == Other::Type) {
            Other* other = dynamic_cast<Other*>(item);
            if (other) {
                Shop* shop = dynamic_cast<Shop*>(other);
                if (shop) {
                    if (shop->sun > cost){
                        AudioManager::instance()->playSound("qrc:/res/level-up.mp3");
                        shop->sun -= cost;
                        cost *= 2;
                        lifetime *= 1.1;
                        hp = (lifetime-hp)/2+hp;
                        atk *= 1.1;
                        product *= 1.1;
                    }
                }
            }
        }
    }
}

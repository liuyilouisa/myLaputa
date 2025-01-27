#include "sun.h"
#include "shop.h"
#include "cloud.h"
#include "audiomanager.h"

Sun::Sun()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> desX(-600, -600+100*5);
    dest = QPointF(desX(gen), 330);
    setPos(QPointF(dest.x(), -450));
    speed = 60.0 * 50 / 1000;
    collected = false;
}

QRectF Sun::boundingRect() const
{
    return QRectF(-45, -45, 90, 90);
}

void Sun::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawPixmap(QRect(-50, -50, 100, 100), QPixmap(":/res/Sun.png"));
}

void Sun::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    if (!collected) {
        AudioManager::instance()->playSound("qrc:/res/sun.mp3");
        collected = true;
        Shop* shop = dynamic_cast<Shop*>(parentItem());
        if (shop) {
            shop->sun += 25;
        }
        delete this;
    }
}

void Sun::advance(int phase)
{
    if (!phase)
        return;
    update();
    if (y() >= dest.y()||collected)
        delete this;
    else if (y() < dest.y())
        setY(y() + speed);
    QGraphicsScene *scene = this->scene();
    if (scene) {
        QList<QGraphicsItem *> collidingItems = scene->collidingItems(this, Qt::IntersectsItemBoundingRect);
        for (QGraphicsItem *item : collidingItems) {
            if (item->type() == Cloud::Type) {
                Shop* shop = dynamic_cast<Shop*>(parentItem());
                Cloud* cloud = dynamic_cast<Cloud *>(item);
                if (shop) {
                    AudioManager::instance()->playSound("qrc:/res/sun.mp3");
                    shop->sun += cloud->product;
                    delete this;
                    return;
                }
            }
        }
    }
}

int Sun::type() const
{
    return Type;
}

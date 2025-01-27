#include "shop.h"
#include "sun.h"
#include "cloud.h"
#include "suncloud.h"
#include "blockcloud.h"
#include "lighteningcloud.h"
#include "snowcloud.h"
#include "raincloud.h"

Shop::Shop() {
    sun = 2000;
    counter = 0;
    time = int(7.0 * 250 / 33);
    Card *card = nullptr;
    for (int i = 0; i < Card::name.size(); ++i)
    {
        card = new Card(Card::name[i]);
        card->setParentItem(this);
        cards.push_back(card);
        card->setPos(1, -160 + 114 * i);
    }
}

QRectF Shop::boundingRect() const
{
    return QRectF(-60,-350,120,710);
}

void Shop::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(QRect(-60,-350,120,710),QPixmap(":/res/shop.png"));
    QFont font;
    font.setPointSizeF(15);
    font.setFamily("Dotted Songti Square");
    painter->setFont(font);
    painter->drawText(QRectF(-30, -257, 65, 22), Qt::AlignCenter, QString::number(sun));
}

void Shop::advance(int phase)
{
    if (!phase)
        return;
    update();
    if (++counter >= time)
    {
        counter = 0;
        Sun *sun = new Sun;
        sun->setParentItem(this);
    }
}

void Shop::addCloud(QString s, QPointF pos)
{
    QList<QGraphicsItem *> items = scene()->items(pos);
    foreach (QGraphicsItem *item, items)
        if (item->type() == Cloud::Type)
            return;
    sun -= Card::cost[Card::map[s]];
    Cloud *cloud = nullptr;
    switch (Card::map[s])
    {
    case 0:
        cloud = new SunCloud; break;
    case 1:
        cloud = new RainCloud; break;
    case 2:
        cloud = new LighteningCloud; break;
    case 3:
        cloud = new BlockCloud; break;
    case 4:
        cloud = new SnowCloud; break;
    }
    cloud->setPos(pos);
    cloud->setFlags(QGraphicsItem::ItemIsSelectable);
    scene()->addItem(cloud);
    cards[Card::map[s]]->counter = 0;
}


void Shop::addSunValue(int value) {
    sun += value;
    update();
}

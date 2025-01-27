#include "card.h"
#include "shop.h"

const QMap<QString, int> Card::map = {{"SunCloud", 0}, {"RainCloud", 1}, {"LighteningCloud", 2}, {"BlockCloud", 3}, {"SnowCloud", 4}};
const QVector<QString> Card::name = {"SunCloud", "RainCloud", "LighteningCloud", "BlockCloud", "SnowCloud"};
const QVector<int> Card::cost = {50, 100, 150, 50, 175};
const QVector<int> Card::cool = {20, 20, 60, 40, 20};

Card::Card(QString s)
{
    text = s;
    counter = 0;
}

QRectF Card::boundingRect() const
{
    return QRectF(-50, -60, 100, 120);
}

void Card::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->scale(0.95, 0.95);
    painter->drawPixmap(QRect(-50, -60, 100, 120), QPixmap(":/res/Card.png"));
    painter->drawPixmap(QRect(-33, -50, 70, 70), QPixmap(":/res/" + text + ".png"));
    QFont font;
    font.setPointSizeF(15);
    font.setFamily("Dotted Songti Square");
    painter->setFont(font);
    painter->drawText(-15, 40, QString().asprintf("%3d", cost[map[text]]));
    if (counter < cool[map[text]])
    {
        QBrush brush(QColor(0, 0, 0, 200));
        painter->setBrush(brush);
        painter->drawRect(QRectF(-50, -60, 100, 120 * (1 - qreal(counter) / cool[map[text]])));
    }
}

void Card::advance(int phase)
{
    if (!phase)
        return;
    update();
    if (counter < cool[map[text]])
        ++counter;
}

void Card::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    if (counter < cool[map[text]])
        event->setAccepted(false);
    Shop *shop = qgraphicsitem_cast<Shop *>(parentItem());
    if (cost[map[text]] > shop->sun)
        event->setAccepted(false);
    setCursor(Qt::ArrowCursor);
}

void Card::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton)).length()
        < QApplication::startDragDistance())
        return;
    QDrag *drag = new QDrag(event->widget());
    QMimeData *mime = new QMimeData;
    QImage image(":/res/" + text + ".png");
    mime->setText(text);
    mime->setImageData(image);
    drag->setMimeData(mime);
    drag->setPixmap(QPixmap::fromImage(image));
    drag->setHotSpot(QPoint(35, 35));
    drag->exec();
    setCursor(Qt::ArrowCursor);
}

void Card::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    setCursor(Qt::ArrowCursor);
}

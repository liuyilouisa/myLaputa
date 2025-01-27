#include "button.h"

Button::Button(QTimer *t){
    timer = t;
}

QRectF Button::boundingRect() const{
    return QRectF(-50, -25, 100, 50);
}

void Button::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawPixmap(QRect(-50, -25, 100, 50), QPixmap(":/res/Button.png"));
    painter->setPen(Qt::black);
    if (timer->isActive()){
        QFont font("Dotted Songti Square", 15, QFont::Bold);
        painter->setFont(font);
        painter->drawText(boundingRect(), Qt::AlignCenter, "PAUSE");
    }
    else{
        QFont font("Dotted Songti Square", 13, QFont::Bold);
        painter->setFont(font);
        painter->drawText(boundingRect(), Qt::AlignCenter, "CONTINUE");
    }
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (timer->isActive()){
            timer->stop();
        }
        else{
            timer->start();
        }
    }
    update();
}


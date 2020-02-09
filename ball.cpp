#include "ball.h"

Ball::Ball(QObject *parent) : QObject(parent), QGraphicsItem()
{
    xspeed = 2*10;
    yspeed = 2*2;
    x = 500;
    y = 285;

}
QRectF Ball::boundingRect() const
{
    return QRectF(0, 0,
                  20, 20);
}

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

        QPolygon polygon;
        painter->setBrush(Qt::black);
        polygon << QPoint(0,0) << QPoint(20,0) << QPoint(20,20) <<  QPoint(0,20);
        painter->drawPolygon(polygon);
        Q_UNUSED(option)
        Q_UNUSED(widget)
}

void Ball::slotGameTimer(){

}
bool Ball::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const{
        QPainterPath path = mapFromItem(other, other->shape());
        QRectF rectA(boundingRect());
        QRectF rectB(path.controlPointRect());
        if (!rectA.intersects(rectB)) {
            // This we can determine efficiently. If the two rects neither
            // intersect nor contain eachother, then the two items do not collide.
            return false;
        }
        QPainterPath intersection = shape().intersected(path);
            if(intersection.isEmpty())
                return false;
        return true;
        Q_UNUSED(mode)
}

int Ball::ballMovement(){

    if(x >= 930)
    {
        reinitiate();
        return 1;
    }
    else if(x  <= -70)
    {
        reinitiate();
        return 2;
    }
    else
    {
    if(y  >= 500 || y <= -70)
        yspeed *= -1;
    x+=xspeed;
    y+=yspeed;

    return 0;
    }
}

void Ball::reinitiate(){
    //xspeed = randSpeed(2, 8, xspeed);//8-10
    //yspeed = randSpeed(3, 3, yspeed);//2-5
    xspeed = 10*1.5;
    yspeed = 2*1.5;
    x = 500;
    y = 0;
}

qreal Ball::randSpeed(int a, int b, qreal x){

    if(qrand()%2)
        x =-1;
    else
        x = 1;
    x *= qrand() % a + b;
    return x;
}

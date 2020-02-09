#include "player1.h"

player1::player1(QObject *parent) : QObject(parent), QGraphicsItem()
{
    player1_width = 40;
    player1_height = 150;
    x = 0;
    y = 0;
    yspeed = 2*8;
}
QRectF player1::boundingRect() const
{
    return QRectF(0, 0,
                  player1_width, player1_height);
}

void player1::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

        QPolygon polygon;
        painter->setBrush(Qt::black);
        polygon << QPoint(0,0) << QPoint(player1_width,0)
                << QPoint(player1_width,player1_height)
                <<  QPoint(0,player1_height);
        painter->drawPolygon(polygon);
        Q_UNUSED(option)
        Q_UNUSED(widget)
}

void player1::player1_movement(){
    if(GetAsyncKeyState(87) && y > -65){
        y-=yspeed;
    }
    if(GetAsyncKeyState(83) && y < 365){
        y+=yspeed;
    }
}


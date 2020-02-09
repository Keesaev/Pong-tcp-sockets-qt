#include "player2.h"

player2::player2(QObject *parent) : QObject(parent), QGraphicsItem()
{
    player2_width = 40;
    player2_height = 150;
    x = 840;
    y = 0;
    yspeed = 2*8;
}

QRectF player2::boundingRect() const
{
    return QRectF(0, 0,
                  player2_width, player2_height);
}

void player2::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

        QPolygon polygon;
        painter->setBrush(Qt::black);
        polygon << QPoint(0,0) << QPoint(player2_width,0)
                << QPoint(player2_width,player2_height)
                <<  QPoint(0,player2_height);
        painter->drawPolygon(polygon);
        Q_UNUSED(option)
        Q_UNUSED(widget)
}

void player2::player2_movement(){
    if(GetAsyncKeyState(VK_UP) && y > -65){
        y-=yspeed;
    }
    if(GetAsyncKeyState(VK_DOWN) && y < 365){
        y+=yspeed;
    }
}



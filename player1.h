#ifndef PLAYER1_H
#define PLAYER1_H


#include <QGraphicsItem>
#include <QPainter>
#include <Qt>
#include "windows.h"

class player1: public QObject, public QGraphicsItem
{
public:
    explicit player1(QObject *parent = nullptr);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
public:
    int x;
    int y;
    int yspeed;
    int player1_width;
    int player1_height;
    void player1_movement();
};



#endif // PLAYER1_H

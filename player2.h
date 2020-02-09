#ifndef PLAYER2_H
#define PLAYER2_H

#include <QGraphicsItem>
#include <QPainter>
#include <Qt>
#include "windows.h"

class player2: public QObject, public QGraphicsItem
{
public:
    explicit player2(QObject *parent = nullptr);
    QRectF boundingRect() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
public:
    int x;
    int y;
    int yspeed;
    int player2_width;
    int player2_height;
    void player2_movement();
};

#endif // PLAYER2_H

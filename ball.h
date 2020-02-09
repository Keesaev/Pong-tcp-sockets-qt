#ifndef BALL_H
#define BALL_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>
#include <QTimer>

class Ball: public QObject, public QGraphicsItem
{
    //Q_OBJECT
public:
    explicit Ball(QObject *parent = nullptr);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    qreal xspeed;
    qreal yspeed;
    qreal x;
    qreal y;

public    slots:
    void slotGameTimer();
    int ballMovement();
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const;
    void reinitiate();
    qreal randSpeed(int a, int b, qreal x);
};

#endif // BALL_H

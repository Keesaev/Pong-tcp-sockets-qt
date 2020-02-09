#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QTime>
#include <ball.h>
#include <player1.h>
#include <player2.h>
#include <QtMath>
#include <QAbstractSocket>
#include <QTcpSocket>
//#include "mainmenu.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class QTcpServer;
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void timerAlert();
    void newGame();
    void on_pushButton_2_released();
    void onNewConnection();
    void onSocketConnected();
    void onSocketDisconnected();
    void onSocketError(QAbstractSocket::SocketError socketError);
    void slotWrite();
    void slotListen();
    void slotRead();
    void slotOutput();

signals:
    void closeSignal();
public:
    QTcpSocket *socket;
    int FPS;
    void ballPhysics();
    QByteArray DataX;
    QByteArray DataY;
    QByteArray DataP1Y;
    QByteArray DataP2Y;

private:
    Ui::Widget *ui;
    QGraphicsScene *scene;
    QTimer *timer;
    Ball *ball;
    player1 *player;
    player2 *player_2;
    QTcpServer* server;

};
#endif // WIDGET_H

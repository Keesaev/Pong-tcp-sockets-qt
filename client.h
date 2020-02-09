#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QTimer>
#include <ball.h>
#include <player1.h>
#include <player2.h>
#include <QTcpSocket>

namespace Ui {
class Client;
}

class Client : public QWidget
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = nullptr);
    ~Client();
private slots:
    void onConnect();
    void onSocketConnected();
    void onSocketDisconnected();
    void onSocketError(QAbstractSocket::SocketError socketError);
    void slotRead();
    void slotWrite();
    void slotOutput();
    void slotBack();
    //void on_pushButton_2_released();
signals:
    void closeSignal();

private:
    Ui::Client *ui;
    QGraphicsScene *scene;
    QTimer *timer;
    Ball *ball;
    player1 *player;
    player2 *player_2;

public:
    QByteArray DataX;
    QByteArray DataY;
    QByteArray DataP1Y;
    QByteArray DataP2Y;
    int FPS;
    QTcpSocket* socket;
};

#endif // CLIENT_H

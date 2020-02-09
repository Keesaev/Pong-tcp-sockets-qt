#include "widget.h"
#include "ui_widget.h"
#include <QTcpSocket>
#include <QTcpServer>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{

    ui->setupUi(this);

    FPS = 45;

    server = new QTcpServer(this);
    timer = new QTimer(this);

    scene = new QGraphicsScene();
    ball = new Ball();
    player = new player1();
    player_2 = new player2();

    connect(server,&QTcpServer::newConnection,this,&Widget::onNewConnection);
    connect(server,&QTcpServer::newConnection,this,&Widget::onSocketConnected);
    connect(timer, SIGNAL(timeout()), this, SLOT(slotWrite()));
    connect(timer, SIGNAL(timeout()), this, SLOT(timerAlert()));
    connect(timer, SIGNAL(timeout()), this, SLOT(slotOutput()));
    connect(ui->pbListen,SIGNAL(released()),this,SLOT(slotListen()));

    connect(ui->pbNewGame, SIGNAL(released()), this, SLOT(newGame()));
    //connect(ui->pbBack,&QPushButton::released,this,&Widget::on_pushButton_2_released);
    //connect(ui->pbBack, SIGNAL(released()), this, SLOT(close()));

    //Установки виджета

    this->setFixedSize(1250,800);

    //Создание сцены и добавление на него объектов

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene->setSceneRect(-60, -60, 1000, 570);

    scene->addItem(player);
    scene->addItem(ball);
    scene->addItem(player_2);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::slotListen()
{
    if(server->listen(QHostAddress::Any,12222))
    {
        ui->textEditInfo->append("Listening");
    }
    else
    {
        ui->textEditInfo->append("Not Listening");
    }
}

void Widget::slotRead(){

    DataP2Y = socket->readAll();
    player_2->y = DataP2Y.toInt();

    player_2->setPos(player_2->x, player_2->y);
}

void Widget::slotWrite()
{
    DataX = QByteArray::number(ball->x);
    DataY = QByteArray::number(ball->y);
    DataP1Y = QByteArray::number(player->y);

    DataX = QByteArray::number(DataX.size()) + DataX;
    DataY = QByteArray::number(DataY.size()) + DataY;
    DataP1Y = QByteArray::number(DataP1Y.size()) + DataP1Y;

    socket->write(DataX);
    socket->write(DataY);
    socket->write(DataP1Y);
}

void Widget::onNewConnection()
{
    socket = new QTcpSocket();
    socket = server->nextPendingConnection();

    connect(socket,&QTcpSocket::readyRead,this,&Widget::slotRead);
    connect(socket,&QTcpSocket::disconnected,this,&Widget::onSocketDisconnected);
    connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(onSocketError(QAbstractSocket::SocketError)));
}

void Widget::onSocketConnected()
{
    ui->textEditInfo->append("Соединение установлено");
    ui->textEditInfo->append("Порт 12222");
    ui->pbNewGame->setEnabled(true);
}

void Widget::onSocketDisconnected()
{
    timer->stop();
    ui->textEditInfo->append("Соединение разорвано");
    QObject* obj = sender();
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(obj);
    socket->deleteLater();
}

void Widget::onSocketError(QAbstractSocket::SocketError socketError)
{
    ui->textEditInfo->append(QString("Произошла ошибка с кодом %1").arg(socketError));
}

void Widget::newGame(){

    timer->start(1000/FPS);

    ui->pbNewGame->setEnabled(false);

    ui->label->setText("0");
    ui->label_2->setText("0");

    ball->setPos(scene->width(),scene->height());
    player->setPos(0,0);
    player_2->setPos(840, 0);

    ball->reinitiate();
    player->y = 0;
    player_2->y = 0;

}

void Widget::timerAlert(){

    //Физика мяча

    ballPhysics();

    //Управление игроками и их отрисовка

    player->player1_movement();
    player->setPos(player->x,player->y);

    //Отрисовка мяча

    ball->setPos(ball->x,ball->y);

}

void Widget::ballPhysics()
{
    //Столкновение с игроком 1

    if(ball->collidesWithItem(player, Qt::ContainsItemShape)){
        if(ball->xspeed > 0)
            ball->xspeed += 0.5;
        else ball->x -= 0.5;

        //ball->yspeed = qrand() % 5 + 2;

        if(ball->x <= 20){
            if(ball->yspeed > 0)
                ball->yspeed = -(qrand() % 7 + 2);
            else
                ball->yspeed = qrand() % 7 + 2;
            //ball->yspeed *=-1;
        }
        else{
            ball->xspeed *=-1;
        }
    }
    //Столкновение с игроком 2
    else
    if(ball->collidesWithItem(player_2, Qt::ContainsItemShape)){
        if(ball->xspeed > 0)
            ball->xspeed += 0.5;
        else ball->x -= 0.5;
        if(ball->x >= 840){
            if(ball->yspeed > 0)
                ball->yspeed = -(qrand() % 7 + 2);
            else
                ball->yspeed = qrand() % 7 + 2;
            //ball->yspeed *=-1;
        }
        else{
            ball->xspeed *=-1;
        }
    }

    //Мяч и границы поля

    int res = ball->ballMovement();

    if(res == 1)
    {
        int score = ui->label->text().toInt()+1;
        QString stringScore = QString::number(score);
        ui->label->setText(stringScore);
    }
    else     if(res == 2)
    {
        int score = ui->label_2->text().toInt()+1;
        QString stringScore = QString::number(score);
        ui->label_2->setText(stringScore);
    }
}

void Widget::on_pushButton_2_released()
{
    emit closeSignal();
}

void Widget::slotOutput(){
    QString x = QString::number(ball->x);
    QString y = QString::number(ball->y);
    QString p1y = QString::number(player->y);
    QString p2y = QString::number(player_2->y);

    ui->textEditCoordinates->setText("x = " + x +
                                     "\ny = " + y +
                                     "\np1y = " + p1y +
                                     "\np2y = " + p2y);
}

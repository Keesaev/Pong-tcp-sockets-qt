#include "client.h"
#include "ui_client.h"
#include <QTcpSocket>

Client::Client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);

    FPS = 45;

    socket = new QTcpSocket(this);

    timer = new QTimer(this);
    scene = new QGraphicsScene();
    ball = new Ball();
    player = new player1();
    player_2 = new player2();

    connect(ui->pbConnect,&QPushButton::clicked,this,&Client::onConnect);
    connect(ui->pbDisconnect,&QPushButton::clicked,this,&Client::onSocketDisconnected);
    connect(ui->pbBack,&QPushButton::clicked,this,&Client::onSocketDisconnected);
    connect(ui->pbBack,&QPushButton::clicked,this,&Client::slotBack);

    connect(timer, SIGNAL(timeout()), this, SLOT(slotWrite()));
    connect(timer, SIGNAL(timeout()), this, SLOT(slotOutput()));
    connect(socket,&QTcpSocket::readyRead,this,&Client::slotRead);

    //Установки виджета

    this->setFixedSize(1250,800);

    //Создание сцены и добавление на него объектов

    ui->graphicsView->setScene(scene);
    //ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene->setSceneRect(-60, -60, 1000, 570);

    scene->addItem(player);
    scene->addItem(ball);
    scene->addItem(player_2);

    //Положение объектов на сцене

    ball->setPos(scene->width(),scene->height());
    player->setPos(0,0);
    player_2->setPos(840, 0);
}

Client::~Client()
{
    delete ui;
}

void Client::slotBack(){
    //
}

void Client::slotWrite(){

    player_2->player2_movement();
    player_2->setPos(player_2->x,player_2->y);

    DataP2Y = QByteArray::number(player_2->y);

    socket->write(DataP2Y);
}

void Client::slotRead()
{
    QByteArray buffer;

    buffer = socket->read(1);
    DataX = socket->read(buffer.toInt());
    ball->x = DataX.toDouble();

    buffer = socket->read(1);
    DataY = socket->read(buffer.toInt());
    ball->y = DataY.toDouble();

    buffer = socket->read(1);
    DataP1Y = socket->read(buffer.toInt());
    player->y = DataP1Y.toInt();

    ball->setPos(ball->x,ball->y);
    player->setPos(player->x, player->y);
}

void Client::onConnect()
{
    //Connect button



    connect(socket,&QTcpSocket::disconnected,this,&Client::onSocketDisconnected);
    connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(onSocketError(QAbstractSocket::SocketError)));

    QString adress = ui->leIP->text();
    quint16 port = 12222;
    socket->connectToHost(adress,port);

    connect(socket,&QTcpSocket::connected,this,&Client::onSocketConnected);
}

void Client::onSocketConnected()
{
    //Socket Connected slot
    timer->start(1000/FPS);
    ui->textEditMessage->append("Соединение установлено");
}

void Client::onSocketDisconnected()
{
    //одну из них убрать
    timer->stop();
    socket->close();
    //socket->deleteLater();
}

void Client::onSocketError(QAbstractSocket::SocketError socketError)
{
    ui->textEditMessage->append(QString("Произошла ошибка с кодом %1").arg(socketError));
}

void Client::slotOutput(){
    QString x = QString::number(ball->x);
    QString y = QString::number(ball->y);
    QString p1y = QString::number(player->y);
    QString p2y = QString::number(player_2->y);

    ui->textEdit->setText("x = " + x +
                          "\ny = " + y +
                          "\np1y = " + p1y +
                          "\np2y = " + p2y);
}

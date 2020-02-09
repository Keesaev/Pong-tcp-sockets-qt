#include "multiplayer.h"
#include "ui_multiplayer.h"

Multiplayer::Multiplayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Multiplayer)
{
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(released()), this, SLOT(hostButton()));
    connect(ui->pushButton_2, SIGNAL(released()), this, SLOT(clientButton()));
}

Multiplayer::~Multiplayer()
{
    delete ui;
}

void Multiplayer::hostButton(){
    w = new Widget();
    w->show();
    this->close();
}

void Multiplayer::clientButton(){
    c = new Client();
    c->show();
    this->close();
}

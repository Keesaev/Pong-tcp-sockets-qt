#include "mainmenu.h"
#include "ui_mainmenu.h"

MainMenu::MainMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);

    connect(ui->pushButton_3, SIGNAL(released()), this, SLOT(ExitButton()));
    connect(ui->pushButton_2, SIGNAL(released()), this, SLOT(MultiplayerButton()));
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::ExitButton(){
    QApplication::quit();
}


void MainMenu::MultiplayerButton(){
    m = new Multiplayer();
    m->show();
    this->close();
}

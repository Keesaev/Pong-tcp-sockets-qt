#ifndef MULTIPLAYER_H
#define MULTIPLAYER_H

#include <QWidget>
#include "widget.h"
#include "client.h"

namespace Ui {
class Multiplayer;
}

class Multiplayer : public QWidget
{
    Q_OBJECT

public:
    explicit Multiplayer(QWidget *parent = nullptr);
    ~Multiplayer();
private slots:
    void hostButton();
    void clientButton();


private:
    Ui::Multiplayer *ui;
    Client *c;
    Widget *w;
};

#endif // MULTIPLAYER_H

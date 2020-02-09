#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include "widget.h"
#include "multiplayer.h"

namespace Ui {
class MainMenu;
}

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();
    Widget *w;
    Multiplayer *m;
protected slots:
    void ExitButton();
    void MultiplayerButton();

private:
    Ui::MainMenu *ui;
};

#endif // MAINMENU_H

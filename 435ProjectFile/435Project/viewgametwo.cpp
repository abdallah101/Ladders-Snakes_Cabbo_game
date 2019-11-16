#include "viewgametwo.h"
#include <mainscreen.h>

ViewGameTwo::ViewGameTwo()
{
}

void ViewGameTwo :: closeEvent(QCloseEvent *bar)
{

    this->close();
    MainScreen * BacktoMain = new MainScreen();
    BacktoMain->setUser(this->user);
    BacktoMain->show();

}

void ViewGameTwo :: setUser(QString a)
{
    this->user = a;
}

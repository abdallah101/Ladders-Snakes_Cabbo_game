#include "viewgametwo.h"
#include <mainscreen.h>


ViewGameTwo::ViewGameTwo()
{
    auto flags = windowFlags();//save current configuration
    //your main configuration which do the trick
    //this->setWindowFlags();
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint );
    //...
    //this->setWindowFlags(flags);//restore
}

/*void ViewGameTwo :: closeEvent(QCloseEvent *bar)
{

    this->close();
    MainScreen * BacktoMain = new MainScreen();
    BacktoMain->setUser(this->user);
    BacktoMain->show();



}*/

void ViewGameTwo :: setUser(QString a)
{
    this->user = a;
}

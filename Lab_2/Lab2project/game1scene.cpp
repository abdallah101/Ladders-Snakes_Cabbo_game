#include "game1scene.h"
#include <QGraphicsScene>
#include <QWidget>
#include <man.h>
#include <rubbish.h>
#include <QTimer>
#include <QApplication>
#include <QGraphicsItem>

game1scene::game1scene()
{
    //Setting background for scene
    this->setSceneRect(0,0,908,510);
    this->setBackgroundBrush(QBrush(QImage(":/images/background.jpg").scaledToHeight(512).scaledToWidth(910)));

    //setting first item (user controlled image) for visual and system control
    background = new man();
    background->setPixmap((QPixmap(":/images/garbageman.jpeg")).scaled(150,150));
    background->setPos(400,365);
    background->setFlag(QGraphicsItem :: ItemIsFocusable);
    background->setFocus();
    this->addItem(background);

    //Timer and signal response procedure for adding rubbish and making them fall
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(2000);

    //Timer and signal response procedure for removing colliding items
    QTimer * timer1 = new QTimer();
    connect(timer1, SIGNAL(timeout()), this, SLOT(collision()));
    timer1 -> start(10);


}


//rubbish add and drop function
void game1scene :: update()
{
   rubbish * rub = new rubbish();
   rub->setPixmap((QPixmap(":/images/rubbish.jpg")).scaled(30,30));
   this->addItem(rub);
   rub->raining();
}

//item remove after collision function
void game1scene :: collision()
{
   for(QGraphicsItem * i : this->collidingItems(background))
   {
       (i->scene())->removeItem(i);
       delete i;
   }
}

#include "rubbish.h"
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <stdlib.h>
#include <QGraphicsScene>
#include <ctime>
rubbish::rubbish(QObject *parent) :
    QObject(parent)
{
    srand(time(0));
    this->setPos((rand()+500) % 900, 0);;
}

//Function to use godown fct every 50 ms (rubbish goes down the y axis "x" pixels every 50ms)

void rubbish :: raining ()
{


        QTimer * timer = new QTimer();
        timer -> start(50);
        connect(timer,SIGNAL(timeout()), this, SLOT(godown()));
}

//function for the rubbish to move down and remove them when out of the window for memory conservation

void rubbish :: godown()
{
    this->setPos(this->x(),this->y()+8);
    if(this->y() > 500)
    {
        scene()->removeItem(this);
        delete this;
    }
}

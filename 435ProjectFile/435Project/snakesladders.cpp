#include "snakesladders.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include<ctime>
#include <QTimer>
#include<stdlib.h>

SnakesLadders::SnakesLadders(QObject *parent) :
    QObject(parent)
{

    srand(time(0));
    this->setPos((rand()+500) % 900, 0);;

}

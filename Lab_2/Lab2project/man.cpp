#include "man.h"

man::man(QObject *parent) :
    QObject(parent)
{
}

//function to move right or left based on a key pressing event

void man :: keyPressEvent(QKeyEvent * event)
{
    if(event->key() == Qt::Key_Right)
    {
    this->setPos(this->x()+15, this->y());
    }
    else if (event->key() == Qt::Key_Left)
    {
        this->setPos(this->x()-15,this->y());
    }
}

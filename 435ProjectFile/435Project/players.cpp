#include "players.h"
#include <QObject>
#include <iostream>
#include <QTimer>
#include <tgmath.h>
#include <QApplication>

players::players(QObject * parent) : QObject(parent)
{
    this->setPos(0,580);
    this->cell = 0;
    active = false;
    steps = 0;
    notFirst = false;

}
int players:: FindCell()
{
    return (this->cell);
}

void players:: MoveP(int step)
{

    notFirst = true;
    active = true;
    double cellsize = 61.2;

    int x;
    int y = ceil((cell+1)/10.0);

        x =(cell + 1)%10;
        if(x == 0)
        {
            x = 10;
        }



    /*double p_x = this->x;
    double p_y = this->y;
    int p_xx = ceil(p_x/cellsize);
    int p_yy = ceil(p_y/cellsize);
    */
    //std::cout << cell << "\n";
    //this->cell += steps;
    steps = step;
    int cur_y = (this->cell + step)/10;
    double cur_x = (this->cell + step) % 10;
    if(cur_y % 2 == 1) cur_x = 9 - cur_x;



    //even levels go left and odd levels go right

    if(y%2 != 0)  //starting level is odd
    {
        if(x <= 4)
        {
            limit = cur_x*cellsize;
            this->activateRight();
        }
        else
        {
            int i = 10 - steps - x;
            if(i >= 0)
            {
                limit = cur_x*cellsize;
                this->activateRight();
            }
            else
            {
                int after = abs(10 - steps - x + 1);
                if(after == 0)
                {
                    limit = 9*61.2;
                    limitup = this->y() - 61.2;
                    this->activateRU();

                }
                else if ( after > 0)
                {
                    limit = 9*61.2;
                    limitup = this->y() - 61.2;
                    limitback = 9*61.2 - after*61.2;
                    activateRUL();
                }

            }
        }
    }

    else //starting level is even
    {
        if(x <= 4)
        {
            limit = cur_x*cellsize;
            this->activateLeft();
        }
        else
        {
            int i = 10 - steps -x;
            if(i >=0)
            {
                limit = cur_x*cellsize;
                this->activateLeft();
            }
            else
            {
                int after = abs(10 - steps - x + 1);
                if(after == 0)
                {
                    limit = 0;
                    limitup = this->y() - 61.2;
                    this->activateLU();

                }
                else if (after > 0)
                {
                    limit = 0;
                    limitup = this->y() - 61.2;
                    limitback = after*61.2;
                    activateLUR();
                }
            }
        }
    }



    //this->setPos(cur_x * cellsize, 580 - cur_y*cellsize);


}

void players:: MovePExtra(int position)
{
    double cellsize = 61.2;
    this-> cell = position;
    int cur_y = cell/10;
    int cur_x = cell % 10;
    if(cur_y % 2 == 1) cur_x = 9 - cur_x;
    this->setPos(cur_x * cellsize, 580 - cur_y*cellsize);
}

void players:: MovePCust(int position)
{
    double cellsize = 51.9;
    this-> cell = position;
    int cur_y = cell/10;
    int cur_x = cell % 10;
    if(cur_y % 2 == 1) cur_x = 9 - cur_x;
    this->setPos(cur_x * cellsize, 520 - 25 - cur_y*cellsize);
}

void players :: activate()
{

    timer = new QTimer();
    timer -> start(1);
    connect(timer,SIGNAL(timeout()), this, SLOT(MoveUp()));


}

void players :: MoveUp()
{

    if (this->y() > limitup)
    {
        this->setPos(this->x(), this->y()-0.1);
    }
    else
    {

        delete timer;
    }

}

void players :: activateLeft()
{
    timer = new QTimer();
    timer -> start(0.5);
    connect(timer,SIGNAL(timeout()), this, SLOT(MoveLeft()));

}

void players :: activateRight()
{

    timer = new QTimer();
    timer -> start(0.5);
    connect(timer,SIGNAL(timeout()), this, SLOT(MoveRight()));



}

void players :: MoveLeft()
{
    if (this->x() >= limit)
    {
        this->setPos(this->x()-0.1, this->y());
    }
    else
    {
        this->cell += steps;
        active = false;
        delete timer;
    }
}

void players :: MoveRight()
{
    if(this->x() <= limit)
    {
        this->setPos(this->x()+0.1, this->y());
    }
    else
    {
        this->cell += steps;
        active = false;
        delete timer;
    }

}

void players :: activateRU()
{
    timer = new QTimer();
    timer -> start(0.5);
    connect(timer,SIGNAL(timeout()), this, SLOT(MoveRU()));



}

void players :: MoveRU()
{
    if(this->x() <= limit)
    {
        this->setPos(this->x()+0.1, this->y());
    }
    else if (this->y() > limitup)
    {
        this->setPos(this->x(), this->y()-0.1);
    }
    else
    {
        this->cell += steps;
        active = false;
        delete timer;
    }

}

void players :: activateLU(){

    timer = new QTimer();
    timer -> start(0.5);
    connect(timer,SIGNAL(timeout()), this, SLOT(MoveLU()));

}

void players :: MoveLU(){

    if(this->x() >= limit)
    {
        this->setPos(this->x()-0.1, this->y());
    }
    else if (this->y() > limitup)
    {
        this->setPos(this->x(), this->y()-0.1);
    }
    else
    {
        this->cell += steps;
        active = false;
        delete timer;
    }

}

void players :: activateLUR()
{
     timer = new QTimer();
    timer -> start(0.5);
    connect(timer,SIGNAL(timeout()), this, SLOT(MoveLUR()));

}


void players :: activateRUL()
{
     timer = new QTimer();
    timer -> start(0.5);
    connect(timer,SIGNAL(timeout()), this, SLOT(MoveRUL()));
}
void players :: MoveRUL()
{
    if(this->x() < limit)
    {
        this->setPos(this->x()+0.1, this->y());

    }
    else if (this->y() > limitup)
    {
        this->setPos(this->x(), this->y()-0.1);
    }

    else if (this->x() > limitback)
    {
          limit = limitback - 1;
          this->setPos(this->x()-0.1, this->y());
    }
    else
    {
        this->cell += steps;
        active = false;
        delete timer;

    }

}
void players :: MoveLUR()
{
    if(this->x() > limit)
    {
        this->setPos(this->x()-0.1, this->y());
    }
    else if (this->y() > limitup)
    {
         this->setPos(this->x(), this->y() - 0.1);
    }

    else if (this->x() < limitback)
    {
        limit = limitback + 1;
        this->setPos(this->x()+0.1, this->y());
    }
    else
    {
        this->cell += steps;
        active = false;
        delete timer;
    }


}




#include "players.h"
#include <QObject>
#include <iostream>
#include <QTimer>
#include <tgmath.h>
#include <QApplication>

players::players(QObject * parent) : QObject(parent)
{
    this->setPos(0,580);
    this->cell = 0;  //here
    active = false;
    steps = 0;
    notFirst = false;
    myturn = false;

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
                    if(y == 10)
                    {
                        limit = 0;
                        limitback = 61.2;
                        this->activateLR();
                        this->cell = 98;

                    }
                    else
                    {
                        limit = 0;
                        limitup = this->y() - 61.2;
                        this->activateLU();
                    }

                }
                else if (after > 0)
                {
                    if(y == 10)
                    {
                        limit = 0;
                        limitback = (after+1)*61.2;
                        this->activateLR();
                        this->cell = 99 - after - 1;
                    }
                    else
                    {
                        limit = 0;
                        limitup = this->y() - 61.2;
                        limitback = after*61.2;
                        activateLUR();
                    }
                }
            }
        }
    }



    //this->setPos(cur_x * cellsize, 580 - cur_y*cellsize);


}

void players:: MovePExtra(int location)
{
    active = true;
    int from = this->cell+1;
    double cellsize = 61.2;
    this-> cell = location;
    int position = location + 1;
    int cur_y = cell/10;
    int cur_x = cell % 10;
    if(cur_y % 2 == 1) cur_x = 9 - cur_x;
    //this->setPos(cur_x * cellsize, 580 - cur_y*cellsize);


    //levelfrom is the starting row level, levelto is the end row level, path is the position of the box
    //that is vertically above the starting position but at the level of the end row
    //these are used to determine if the ending position is at the left or right of the starting position

    int levelfrom, levelto, path, height;
    levelfrom = ceil(from/10.0);
    levelto = ceil(position/10.0);

    height = abs(levelfrom - levelto);




    //this->setPos(cur_x * cellsize, 580 - cur_y*cellsize);
    if(position > from) //ladder

    {
    //*****************************************************************************************

        if(levelfrom%2==0 && levelto%2!=0)
        {

            if(from%10 == 0)
            {
                path = levelto*10 - 9;
            }
            else
            {
                path = levelto*10 - (from%10 - 1);
            }

        }
        else if (levelfrom%2!=0 && levelto%2==0)
        {
            if(from%10 == 0)
            {
                path = levelto*10 - (9);
            }
            else
            {
                path = levelto*10 - (from%10 - 1);
            }
        }
        else
        {
            path = from + height*10;
        }

        if(path == position)
        {
            limitup = this->y() - 61.2*(height);
            activate();
        }

    else if(levelto%2==0)
    {
        if(path > position)  //left to right
        {
            maxX = cur_x * cellsize;
            maxY = this->y() - 61.2*height;
            ratioY = (this->y() - maxY)/(maxX - this->x());
            activateLadderUR();

        }
        //**********************************************************************************
        else //right to left
        {

            maxX = cur_x * cellsize;
            maxY = this->y() - 61.2*height;
            ratioY = (this->y() - maxY)/(this->x() - maxX);
            activateLadderUL();
        }
    }
    //******************************************************************************************
    else
    {
        if(path > position)  //right to left
        {

            maxX = cur_x * cellsize;
            maxY = this->y() - 61.2*height;
            ratioY = (this->y() - maxY)/(this->x() - maxX);
            activateLadderUL();


        }
        //**************************************************************************************
        else  //left to right
        {

            maxX = cur_x * cellsize;
            maxY = this->y() - 61.2*height;
            ratioY = (this->y() - maxY)/(maxX - this->x());
            activateLadderUR();


        }
    }

    }
    else //here for the snakes
    {
        int j = levelfrom;
        levelfrom = levelto;
        levelto = j;

        j = from;
        from = position;
        position = j;

        if(levelfrom%2==0 && levelto%2!=0)
        {

            if(from%10 == 0)
            {
                path = levelto*10 - 9;
            }
            else
            {
                path = levelto*10 - (from%10 - 1);
            }

        }
        else if (levelfrom%2!=0 && levelto%2==0)
        {
            if(from%10 == 0)
            {
                path = levelto*10 - (9);
            }
            else
            {
                path = levelto*10 - (from%10 - 1);
            }
        }
        else
        {
            path = from + height*10;
        }

        if(path == position)
        {
            limitup = this->y() + 61.2*height;
            activateMoveDown();
        }

        else if(levelto%2==0)
        {
            if(path > position)  //left to right
            {
                maxX = cur_x * cellsize;
                maxY = this->y() + 61.2*height;
                ratioY = (maxY - this->y() )/(this->x() - maxX);
                activateSnakeDL();

            }
            //**********************************************************************************
            else //right to left
            {

                maxX = cur_x * cellsize;
                maxY = this->y() + 61.2*height;
                ratioY = (maxY - this->y())/(maxX - this->x());
                activateSnakeDR();


            }
        }
        //******************************************************************************************
        else
        {
            if(path > position)  //right to left
            {

                maxX = cur_x * cellsize;
                maxY = this->y() + 61.2*height;
                ratioY = (maxY - this->y())/(maxX - this->x());
                activateSnakeDR();


            }
            //**************************************************************************************
            else  //left to right
            {

                maxX = cur_x * cellsize;
                maxY = this->y() + 61.2*height;
                ratioY = (maxY - this->y())/(this->x() - maxX);
                activateSnakeDL();


            }
        }

    }

    //**********************************************************************************************
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
        active = false;
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
void players :: activateLadderUR(){
   timerLS = new QTimer();
   timerLS -> start(1.5);
   connect(timerLS,SIGNAL(timeout()), this, SLOT(LadderUR()));
}
void players :: activateLadderUL(){
    timerLS = new QTimer();
    timerLS -> start(1.5);
    connect(timerLS,SIGNAL(timeout()), this, SLOT(LadderUL()));
}
void players :: LadderUR(){


    if(this->x() < maxX || this->y() > maxY)
    {
        this->setPos(this->x() +0.1/ratioY , this->y() - 0.1);
    }
    else
    {
        active = false;
        delete timerLS;
    }

}
void players :: LadderUL(){

    if(this->x() > maxX || this->y() > maxY)
    {
        this->setPos(this->x() -0.1/ratioY , this->y() - 0.1);
    }
    else
    {
        active = false;
        delete timerLS;
    }

}
void players :: activateSnakeDL(){
    timerLS = new QTimer();
    timerLS -> start(1.5);
    connect(timerLS,SIGNAL(timeout()), this, SLOT(SnakeDL()));
}
void players :: activateSnakeDR(){
    timerLS = new QTimer();
    timerLS -> start(1.5);
    connect(timerLS,SIGNAL(timeout()), this, SLOT(SnakeDR()));
}
void players :: SnakeDR(){


    if(this->x() < maxX || this->y() < maxY)
    {
        this->setPos(this->x() + 0.1/ratioY , this->y() + 0.1);
    }
    else
    {
        active = false;
        delete timerLS;
    }

}
void players :: SnakeDL(){


    if(this->x() > maxX || this->y() < maxY)
    {
        this->setPos(this->x() - 0.1/ratioY , this->y() + 0.1);
    }
    else
    {
        active = false;
        delete timerLS;
    }
}
void players :: activateMoveDown(){
    timer = new QTimer();
    timer -> start(0.5);
    connect(timer,SIGNAL(timeout()), this, SLOT(MoveDown()));
}
void players :: MoveDown()
{
    if (this->y() < limitup)
    {
        this->setPos(this->x(), this->y()+0.1);
    }
    else
    {
        active = false;
        delete timer;
    }
}

void players :: activateLR()
{
    timer = new QTimer();
    timer -> start(0.8);
    connect(timer,SIGNAL(timeout()), this, SLOT(MoveLR()));
}
void players :: MoveLR()
{
    if(this->x() > limit)
    {
        this->setPos(this->x()-0.1, this->y());
    }
    else if (this->x() < limitback)
    {
        limit = limitback + 1;
        this->setPos(this->x()+0.1, this->y());
    }
    else
    {

        active = false;
        delete timer;
    }
}




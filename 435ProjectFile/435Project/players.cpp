#include "players.h"
#include <QObject>
#include <iostream>

players::players(QObject * parent) : QObject(parent)
{
    this->setPos(0,580);
    this->cell = 0;
}
int players:: FindCell()
{
    return (this->cell);
}

void players:: MoveP(int steps)
{
    double cellsize = 61.2;
    /*double p_x = this->x;
    double p_y = this->y;
    int p_xx = ceil(p_x/cellsize);
    int p_yy = ceil(p_y/cellsize);
    */
    //std::cout << cell << "\n";
    this->cell += steps;
    int cur_y = cell/10;
    int cur_x = cell % 10;
    if(cur_y % 2 == 1) cur_x = 9 - cur_x;
    this->setPos(cur_x * cellsize, 580 - cur_y*cellsize);
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

/*
int cell;
void MoveP(int);
int FindCell();
*/

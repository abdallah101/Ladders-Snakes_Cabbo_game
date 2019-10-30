#include "game1_scene.h"
#include <QApplication>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QWidget>
#include <QTimer>
#include <QFile>
#include <QPixmap>
#include <QImage>
#include <QDir>
#include <players.h>
game1_scene::game1_scene()
{


    /**
      *Initialize the grid of the game
      */
    for (int i=0;i<100; i++)
    {
        grid[i] = 0;
    }
    grid[0] = 37;
    grid[3] = 13;
    grid[8] = 30;
    grid[20] = 41;
    grid[27] = 83;
    grid[50] = 66;
    grid[70] = 90;
    grid[79] = 99;
    grid[16] = 6;
    grid[61] = 18;
    grid[63] = 59;
    grid[53] = 33;
    grid[86] = 23;
    grid[92] = 72;
    grid[94] = 74;
    grid[97] = 78;

    /*! \brief Scaling the background
     */

    /**
      * Setting background for scene
      */
    this->setSceneRect(0,0,612, 612);
    QImage green;

    if (green.load(QDir::currentPath() + "/Images/SL.jpg"))
    {
        //green.scaledToWidth(this->width(), Qt::SmoothTransformation);
        //green.scaled(500,500);
        this->setBackgroundBrush(QBrush(green.scaledToHeight(612).scaledToWidth(612)));

    }
    player1 = new players();
    player1->setPixmap((QPixmap(QDir::currentPath() + "/Images/yellow.png")).scaled(30,30));
    player2 = new players();

    /**
      * add 30 offset between player 1 and 2 to avoid overlap
      */

    player2->setPos(player2->x() , player2->y() - 30);
    player2->setPixmap((QPixmap(QDir::currentPath() + "/Images/purple.jpg")).scaled(30,30));
    this->addItem(player1);
    this->addItem(player2);




}


void game1_scene::Move(players * player, int steps)
{

    player->MoveP(steps);

}

void game1_scene :: check (players * player)
{
    if (player->notFirst == true )
    {
        if(grid[player->cell] != 0)
            player->MovePExtra(grid[player->cell]);
    }
}


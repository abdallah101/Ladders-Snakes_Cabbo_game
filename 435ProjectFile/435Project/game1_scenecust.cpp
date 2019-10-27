#include "game1_scenecust.h"
#include <QDir>
#include <iostream>
game1_sceneCust::game1_sceneCust()
{
    /**
      *Initialize the grid of the game
      */

    for (int i=0;i<100; i++)
    {
        gridCust[i] = 0;
    }

    this->setSceneRect(0,0,518, 520);
    QImage green;
    if (green.load(QDir::currentPath() + "/Images/grid.PNG"))
    {
        this->setBackgroundBrush(QBrush(green.scaledToHeight(518).scaledToWidth(520)));
    }

    player1Cust = new players;
    player1Cust->setPixmap((QPixmap(QDir::currentPath() + "/Images/yellow.png")).scaled(25,25));
    player1Cust->setPos(0 , 520 - 25);

    player2Cust = new players;

    /**
      * add 30 offset between player 1 and 2 to avoid overlap
      */

    player2Cust->setPos(0 , 520 - 25 - 25);
    player2Cust->setPixmap((QPixmap(QDir::currentPath() + "/Images/purple.jpg")).scaled(25,25));

    this->addItem(player1Cust);
    this->addItem(player2Cust);
}

void game1_sceneCust::MoveCust(players * player, int steps)
{
    int destination = player->cell + steps;
    std::cout << destination << "\n";
    if(gridCust[destination] != 0) destination = gridCust[destination];
    player->MovePCust(destination);
    std::cout << player->cell << "\n";
}

void game1_sceneCust::AddLadderSnake(int cellFrom, int cellTo)
{
    this->gridCust[cellFrom-1] = cellTo - 1;
}

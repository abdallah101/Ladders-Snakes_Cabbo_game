#ifndef GAME1_SCENECUST_H
#define GAME1_SCENECUST_H
#include <players.h>
#include <QGraphicsScene>
class game1_sceneCust: public QGraphicsScene
{

public:
    game1_sceneCust();
    players * player1Cust, * player2Cust;
    int gridCust[100];

public slots:
      void MoveCust(players * , int);
      void AddLadderSnake(int, int);
};

#endif // GAME1_SCENECUST_H

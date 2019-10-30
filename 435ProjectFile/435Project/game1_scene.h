#ifndef GAME1_SCENE_H
#define GAME1_SCENE_H
#include <QGraphicsScene>
#include <players.h>
#include <QTimer>
class game1_scene : public QGraphicsScene
{
  Q_OBJECT
public:
    game1_scene();
    players * player1, * player2;
    void Move(players * , int);
    int grid[100];




public slots:
    void check (players * player);


};

#endif // GAME1_SCENE_H

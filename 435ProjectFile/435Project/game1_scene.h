#ifndef GAME1_SCENE_H
#define GAME1_SCENE_H
#include <QGraphicsScene>
#include <players.h>
class game1_scene : public QGraphicsScene
{
public:
    game1_scene();
    players * player1, * player2;
};

#endif // GAME1_SCENE_H

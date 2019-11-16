#ifndef GAME2_SCENE_H
#define GAME2_SCENE_H

#include <QGraphicsScene>
#include <cards.h>

class game2_scene : public QGraphicsScene
{
     Q_OBJECT
public:
    game2_scene();
    Cards * playerCards1, * playerCards2, * playerCards3, * playerCards4, * playerCards5,
    * playerCards6, * playerCards7, * playerCards8, * playerCards9, * playerCards10, * playerCards11
    ,* playerCards12;
    Cards * fromPile, * toPile;


    int pile[52];
public slots:

};

#endif // GAME2_SCENE_H

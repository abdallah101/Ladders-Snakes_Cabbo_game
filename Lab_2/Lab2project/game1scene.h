#ifndef GAME1SCENE_H
#define GAME1SCENE_H
#include <QGraphicsScene>
#include <QWidget>
#include <QGraphicsPixmapItem>
#include <man.h>
#include <rubbish.h>

class game1scene : public QGraphicsScene
{
    Q_OBJECT
public:
    game1scene();

private:

    man * background;
    rubbish * rub;

public slots:

void update();
void collision();


};

#endif // GAME1SCENE_H

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
    /*! \brief Scaling the background
     */
    //Setting background for scene



    this->setSceneRect(0,0,612, 612);


    QImage green;

    if (green.load(QDir::currentPath() + "/Images/SL.jpg"))
    {
        //green.scaledToWidth(this->width(), Qt::SmoothTransformation);
        //green.scaled(500,500);
        this->setBackgroundBrush(QBrush(green.scaledToHeight(612).scaledToWidth(612)));

    }
    player1 = new players;
    player1->setPixmap((QPixmap(QDir::currentPath() + "/Images/yellow.png")).scaled(30,30));
    player2 = new players;
    player2->setPos(player2->x() , player2->y() - 30); // avoid overlap
    player2->setPixmap((QPixmap(QDir::currentPath() + "/Images/purple.jpg")).scaled(30,30));
    this->addItem(player1);
    this->addItem(player2);
}


void game1_scene::Move(players * player, int steps)
{
    player->MoveP(steps);
}


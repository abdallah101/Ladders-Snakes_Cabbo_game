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

}

void game1_scene::Move(players * player, int steps)
{
    player-> MoveP(steps);
}

#include "gameone.h"
#include <QApplication>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QWidget>
#include <QTimer>
#include <QFile>
#include <QPixmap>
#include <QImage>
#include <QDir>
#include <dice.h>
GameOne::GameOne(QWidget *parent) :
    QWidget(parent)

{
    startButton = new QPushButton ("New Game");
    Horiz = new QGridLayout();
    Horiz->addWidget(startButton,200,200);
    this->setLayout(Horiz);
    this->resize(400, 400);
    QObject::connect(startButton, SIGNAL(clicked()), this, SLOT(start()) );
}

void GameOne :: start()
{
    this->close();
    scene = new dice();
    scene->show();

}



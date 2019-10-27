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
#include <custWid.h>
GameOne::GameOne(QWidget *parent) :
    QWidget(parent)

{
    startButton = new QPushButton ("New Game");
    SetLaddersSnakes = new QPushButton ("Customize the positions of snakes and ladders.");
    Horiz = new QGridLayout();
    Horiz->addWidget(startButton,0,0);
    Horiz->addWidget(SetLaddersSnakes,1,0);
    this->setLayout(Horiz);
    this->resize(200, 200);
    QObject::connect(startButton, SIGNAL(clicked()), this, SLOT(start()));
    QObject::connect(SetLaddersSnakes, SIGNAL(clicked()), this, SLOT(customize()));
}

void GameOne :: start()
{
    this->close();
    scene = new dice();
    scene->show();

}

void GameOne :: customize()
{
    this->close();
    scene = new custWid();
    scene->show();

}

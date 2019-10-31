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
#include <game1_modes.h>
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
    scene = new Game1_Modes();
    //scene->SetUser(this->user, this->name);
    scene->show();

}

void GameOne :: customize()
{
    this->close();
    scene1 = new custWid();
    scene1->SetUser(this->user);
    scene1->show();
}

void GameOne :: SetUser (QString d, QString n)
{
    this->user = d;
    this->name = n;
}

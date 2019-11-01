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
    easy = new QRadioButton("easy");
    medium = new QRadioButton("medium");
    hard = new QRadioButton("hard");
    twoplayers = new QRadioButton("2 players");
    choose = new QLabel("Choose difficulty");
    VerticalRadioB = new QVBoxLayout();
    GP = new QGroupBox();
    error = new QLabel("");

    VerticalRadioB->addWidget(easy);
    VerticalRadioB->addWidget(medium);
    VerticalRadioB->addWidget(hard);
    VerticalRadioB->addWidget(twoplayers);
    GP->setLayout(VerticalRadioB);


    Horiz = new QGridLayout();
    Horiz->addWidget(startButton,0,0);
    Horiz->addWidget(GP,1,0);
    Horiz->addWidget(SetLaddersSnakes,2,0);
    Horiz->addWidget(error,3,0);
    this->setLayout(Horiz);
    this->resize(200, 200);
    QObject::connect(startButton, SIGNAL(clicked()), this, SLOT(start()));
    QObject::connect(SetLaddersSnakes, SIGNAL(clicked()), this, SLOT(customize()));

    /**
     * removes message after 4 seconds
     */
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

}

void GameOne :: start()
{

    if(!easy->isChecked() && !medium->isChecked() && !hard->isChecked() && !twoplayers->isChecked())
    {
        error->setText("Choose difficulty first!");
        timer->start(4000);
    }
    else if(easy->isChecked())
    {
        this->close();
        scene = new dice();
        scene->difficulty = 1;
        scene->SetUser(this->user, this->name);
        scene->show();
    }
    else if (medium->isChecked())
    {
        this->close();
        scene = new dice();
        scene->difficulty = 2;
        scene->SetUser(this->user, this->name);
        scene->show();
    }
    else if (hard->isChecked())
    {
        this->close();
        scene = new dice();
        scene->difficulty = 3;
        scene->SetUser(this->user, this->name);
        scene->show();
    }
    else if (twoplayers->isChecked())
    {
        this->close();
        scene = new dice();
        scene->difficulty = 4;
        scene->SetUser(this->user, this->name);
        scene->show();
    }



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

void GameOne :: update ()
{
    error->setText("");
}

#include "starter.h"
#include <QApplication>
#include <QObject>
#include <QtWidgets>
#include <stdio.h>
#include <stdlib.h>
#include <dice.h>

Starter::Starter(QWidget *parent) :
    QWidget(parent)
{


    player1 = new QLabel("Player1: 0");
    player2 = new QLabel("Player2: 0");
    message = new QLabel("Roll Die to determine who starts!");
    error = new QLabel();
    rolldie = new QPushButton("Roll The Die");
    done = new QPushButton("Done");
    GP = new QGroupBox();
    hori = new QGridLayout();
    vert = new QVBoxLayout();
    rolledit = false;

   hori->addWidget(player1,0,0);
   hori->addWidget(player2,0,1);
   GP->setLayout(hori);
   vert->addWidget(message);
   vert->addWidget(GP);
   vert->addWidget(rolldie);
   vert->addWidget(done);
   vert->addWidget(error);

   this->setLayout(vert);


   /**
     * Signal connector to roll the die
     */

    QObject::connect(rolldie, SIGNAL(clicked()), this, SLOT(roll()) );

    /**
      * Signal connector to go to game1 scene
      */

     QObject::connect(done, SIGNAL(clicked()), this, SLOT(Back()) );

}

void Starter :: roll ()
{

    if(rolledit == false) //so that players roll only once
    {
    srand(time(0));

    int x = rand() % 7;
    QString sx = "";
    sx += (x + '0');
    //player1->setText(sx);

    player1->setText("Player1: " + QString::number(x));

    int j = x;
    x = rand() % 7;
    sx = "";
    sx += (x + '0');
    //player1->setText(sx);

    player2->setText("Player2: " + QString::number(x));
    rolledit = true;

    if(x > j)
    {winningPlayer = 2;}
    else
    {winningPlayer = 1;}



    }
    else
    {
        error->setText("Already rolled! Press done to countinue");
    }
}

void Starter :: Back()
{
    if(rolledit == true)
    {
    this->close();
    scene = new dice();

    scene->SetUser(this->user, this->name, this->difficultyS, this->winningPlayer);

    scene->show();
    }
    else
    {
        error->setText("Roll the Dice first!");
    }
}

void Starter :: SetUser (QString a, QString b, int S)
{
    this->user = a;
    this->name = b;
    this->difficultyS = S;
}

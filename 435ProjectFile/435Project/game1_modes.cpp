#include "game1_modes.h"
#include "dice.h"
#include "mainmenu_widget.h"
#include <QApplication>
#include <QWidget>
#include <QtWidgets>
#include <strings.h>
#include <QLabel>
#include <QLayout>
#include <registermenu.h>
#include <QFile>
#include <QTextStream>
#include <mainscreen.h>
#include <QPalette>
#include <QPixmap>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
/**
  *\file Game1_Modes.cpp
  */

Game1_Modes::Game1_Modes(QWidget *parent):
    QWidget(parent)
{
    ComputerEasy = new QPushButton("Vs Computer: Easy");
    ComputerHard = new QPushButton("Vs Computer: Hard");
    Players2 = new QPushButton("2 Players");
    HMode = new QGridLayout;
    HMode->addWidget(ComputerEasy, 0, 0);
    HMode->addWidget(ComputerHard, 1, 0);
    HMode->addWidget(Players2, 2, 0);
    this->setLayout(HMode);
    this->show();

    /**
    * Signal connector to start a game against computer with level of difficulty: easy
    */

   QObject::connect(ComputerEasy, SIGNAL(clicked()), this, SLOT(start1()) );

   /**
   * Signal connector to start a game against computer with level of difficulty: hard
   */

  QObject::connect(ComputerHard, SIGNAL(clicked()), this, SLOT(start2()) );
  /**
  * Signal connector to start a game with 2 players
  */

 QObject::connect(Players2, SIGNAL(clicked()), this, SLOT(start3()) );

}
void Game1_Modes::start1()
{

}

void Game1_Modes::start2()
{

}

void Game1_Modes::start3()
{
     this->close();
     nxtscene = new dice();
     //nxtscene->SetUser(this->user,this->name);
     nxtscene->show();
}

void Game1_Modes :: SetUser(QString a, QString b)
{
    this->user = a;
    this->name = b;
}

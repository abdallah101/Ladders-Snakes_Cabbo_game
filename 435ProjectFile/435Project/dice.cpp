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
  *\file dice.cpp
  */

dice::dice(QWidget *parent) :
    QWidget(parent)
{
    /**
     * Creating buttons, input boxes, and Labels
     */

    ThrowBlue_Button = new QPushButton("Throw both die");
    //ThrowRed_Button = new QPushButton("Throw red die");
    EndTurn_Button = new QPushButton("End Turn");
    EndGame_Button = new QPushButton("End Game");

    PlayerUsername = new QLabel("Player " + name);
    blue = new QRadioButton("blue");
    red = new QRadioButton("red");
    Game1Scene = new game1_scene();
    Game1_View = new QGraphicsView();

    /**
     * Creating layouts
     */

    Horizental = new QGridLayout();
    VerticalDice = new QVBoxLayout();


    /**
     * Adding widgets to horizantel layout
    */

    Horizental->addWidget(PlayerUsername,0,0);
   // VerticalDice->addItem(Horizental);
    Horizental->addWidget(ThrowBlue_Button,1,0);
    Horizental->addWidget(blue,2,0);
    //Horizental->addWidget(ThrowRed_Button,2,0);
    Horizental->addWidget(red,3,0);
    Horizental->addWidget(EndTurn_Button,4,0);
    Horizental->addWidget(EndGame_Button,5,0);
    this->setLayout(Horizental);
    this->resize(400, 400);

   /**
     * Signal connector to throw the blue die
     */

    QObject::connect(ThrowBlue_Button, SIGNAL(clicked()), this, SLOT(ThrowBlue()) );

    /**
     * Signal connector to end a player's turn
     */
    QObject::connect(EndTurn_Button, SIGNAL(clicked()), this, SLOT(EndTurn()) );

    /**
     * Signal connector to main screen
     */
    QObject::connect(EndGame_Button, SIGNAL(clicked()), this, SLOT(EndGame()) );

    /**
     * removes message after 4 seconds
     */
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(4000);


    Game1_View->setScene(Game1Scene);
    Game1_View->setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    Game1_View->setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    Game1_View->show();
}

/**
 * \brief Function to throw blue die and red die
 * \param Takes no parameter
 * \return nothing (type: void)
 */

void dice :: ThrowBlue()
{
    srand(time(0));
    int x = rand() % 7;
    QString sx = "";
    sx += (x + '0');
    blue->setText(sx);
    blueval = x;
    blue->setText(QString::number(blueval));

    x = rand() % 7;
    sx = "";
    sx += (x + '0');
    red->setText(sx);
    redval = x;
    red->setText(QString::number(redval));
}




/**
 * \brief Function that ends a game
 * \param Takes no parameter
 * \return nothing (type: void)
 */

void dice :: EndGame()
{
    Game1_View->close();
    this->close();
    BackToMain = new MainScreen();
    BackToMain->setUser(this->user);
    BackToMain->show();
}

/**
 * \brief Function that ends a player's turn
 * \param Takes no parameter
 * \return nothing (type: void)
 */

void dice :: EndTurn()
{
    Game1Scene->Move(Game1Scene->player1, blueval);
    Game1Scene->Move(Game1Scene->player2, redval);
    Game1Scene->player2->setPos(Game1Scene->player2->x(), Game1Scene->player2->y() - 30);
    //this->close();
}

void dice :: SetUser (QString d, QString n)
{
    this->user = d;
    this->name = n;
    PlayerUsername->setText("Player " + name);
}


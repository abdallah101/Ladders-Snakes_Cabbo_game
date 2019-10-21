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

/**
  *\file dice.cpp
  */

dice::dice(QWidget *parent) :
    QWidget(parent)
{
    /**
     * Creating buttons, input boxes, and Labels
     */

    ThrowBlue_Button = new QPushButton("Throw blue die");
    ThrowRed_Button = new QPushButton("Throw red die");
    EndTurn_Button = new QPushButton("End Turn");
    EndGame_Button = new QPushButton("End Game");

    PlayerUsername = new QLabel("Player x");
    blue = new QLabel();
    red = new QLabel();
    Game1Scene = new game1_scene();


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
    Horizental->addWidget(blue,1,4);
    Horizental->addWidget(ThrowRed_Button,2,0);
    Horizental->addWidget(red,2,4);
    Horizental->addWidget(EndTurn_Button,3,0);
    Horizental->addWidget(EndGame_Button,4,0);
    this->setLayout(Horizental);
    this->resize(400, 400);

   /**
     * Signal connector to throw the blue die
     */

    QObject::connect(ThrowBlue_Button, SIGNAL(clicked()), this, SLOT(ThrowBlue()) );

    /**
     * Signal connector to throw the red die
     */
    QObject::connect(ThrowRed_Button, SIGNAL(clicked()), this, SLOT(ThrowRed()) );

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


}

/**
 * \brief Function to throw blue die
 * \param Takes no parameter
 * \return nothing (type: void)
 */

void dice :: ThrowBlue()
{
    srand(time(NULL));
    int x = rand() % 7;
    QString sx = "";
    sx += (x + '0');
    blue->setText(sx);
}

/**
 * \brief Function to throw red die
 * \param Takes no parameter
 * \return nothing (type: void)
 */

void dice :: ThrowRed()
{
    srand(time(NULL));
    int x = rand() % 7;
    QString sx = "";
    sx += (x + '0');
    red->setText(sx);
}

/**
 * \brief Function that ends a game
 * \param Takes no parameter
 * \return nothing (type: void)
 */

void dice :: EndGame()
{
    this->close();
    BackToMain = new MainScreen();
    BackToMain->show();
}

/**
 * \brief Function that ends a player's turn
 * \param Takes no parameter
 * \return nothing (type: void)
 */

void dice :: EndTurn()
{
    this->close();
    QGraphicsView * Game1_View = new QGraphicsView();
    Game1_View->setScene(Game1Scene);
    Game1_View->setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    Game1_View->setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    Game1_View->show();
}

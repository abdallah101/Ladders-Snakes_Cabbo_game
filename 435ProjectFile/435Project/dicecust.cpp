#include "dicecust.h"

#include <QPixmap>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

/**
  *\file dice.cpp
  */

diceCust::diceCust(QWidget *parent) :
    QWidget(parent)
{
    /**
     * Creating buttons, input boxes, and Labels
     */

    ThrowBlue_ButtonCust = new QPushButton("Throw blue die");
    ThrowRed_ButtonCust = new QPushButton("Throw red die");
    EndTurn_ButtonCust = new QPushButton("End Turn");
    EndGame_ButtonCust = new QPushButton("End Game");

    PlayerUsernameCust = new QLabel("Player x");
    blueCust = new QLabel();
    redCust = new QLabel();


    Game1Cust = new  game1_sceneCust();
    Game1_ViewCust = new QGraphicsView();

    /**
     * Creating layouts
     */

    HorizentalCust = new QGridLayout();
    VerticalDiceCust = new QVBoxLayout();


    /**
     * Adding widgets to horizantel layout
    */

    HorizentalCust->addWidget(PlayerUsernameCust,0,0);
   // VerticalDice->addItem(Horizental);
    HorizentalCust->addWidget(ThrowBlue_ButtonCust,1,0);
    HorizentalCust->addWidget(blueCust,1,4);
    HorizentalCust->addWidget(ThrowRed_ButtonCust,2,0);
    HorizentalCust->addWidget(redCust,2,4);
    HorizentalCust->addWidget(EndTurn_ButtonCust,3,0);
    HorizentalCust->addWidget(EndGame_ButtonCust,4,0);
    this->setLayout(HorizentalCust);
    this->resize(400, 400);

   /**
     * Signal connector to throw the blue die
     */

    QObject::connect(ThrowBlue_ButtonCust, SIGNAL(clicked()), this, SLOT(ThrowBlueCust()) );

    /**
     * Signal connector to throw the red die
     */
    QObject::connect(ThrowRed_ButtonCust, SIGNAL(clicked()), this, SLOT(ThrowRedCust()) );

    /**
     * Signal connector to end a player's turn
     */
    QObject::connect(EndTurn_ButtonCust, SIGNAL(clicked()), this, SLOT(EndTurnCust()) );

    /**
     * Signal connector to main screen
     */
    QObject::connect(EndGame_ButtonCust, SIGNAL(clicked()), this, SLOT(EndGameCust()) );

    /**
     * removes message after 4 seconds
     */
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(4000);


    Game1_ViewCust->setFixedSize(518,520);
    Game1_ViewCust->setScene(Game1Cust); 
    Game1_ViewCust->setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    Game1_ViewCust->setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    Game1_ViewCust->show();
}

/**
 * \brief Function to throw blue die
 * \param Takes no parameter
 * \return nothing (type: void)
 */

void diceCust :: ThrowBlueCust()
{
    srand(time(NULL));
    int x = 1 + rand() % 6;
    QString sx = "";
    sx += (x + '0');
    blueCust->setText(sx);
    bluevalCust = x;
}

/**
 * \brief Function to throw red die
 * \param Takes no parameter
 * \return nothing (type: void)
 */

void diceCust :: ThrowRedCust()
{
    srand(time(NULL));
    int x = 1 + rand() % 6;
    QString sx = "";
    sx += (x + '0');
    redCust->setText(sx);
    redvalCust = x;
}


/**
 * \brief Function that ends a game
 * \param Takes no parameter
 * \return nothing (type: void)
 */

void diceCust :: EndGameCust()
{
    Game1_ViewCust->close();
    this->close();
    BackToMainCust = new MainScreen();
    BackToMainCust->show();
}

/**
 * \brief Function that ends a player's turn
 * \param Takes no parameter
 * \return nothing (type: void)
 */

void diceCust :: EndTurnCust()
{

   Game1Cust->MoveCust(Game1Cust->player1Cust, bluevalCust);
   Game1Cust->MoveCust(Game1Cust->player2Cust, redvalCust);
   Game1Cust->player2Cust->setPos(Game1Cust->player2Cust->x(), Game1Cust->player2Cust->y() - 25);
    //this->close();
}



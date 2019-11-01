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
    error = new QLabel("");
    VerticalRadioB = new QVBoxLayout();
    GP = new QGroupBox();
    choose = new QLabel("Choose!");
    endedturn = false;
    /**
     * Creating layouts
     */

    Horizental = new QGridLayout();
    VerticalDice = new QVBoxLayout();
    Vertical = new QVBoxLayout();


    /**
     * Adding widgets to horizantel layout
    */

    VerticalRadioB->addWidget(blue);
    VerticalRadioB->addWidget(red);
    GP->setLayout(VerticalRadioB);
    Vertical->addWidget(PlayerUsername,0,0);
   // VerticalDice->addItem(Horizental);
    Vertical->addWidget(ThrowBlue_Button,1,0);
    Horizental->addWidget(GP,2,0);
    Horizental->addWidget(choose,2,1);
    //Horizental->addWidget(ThrowRed_Button,2,0);

    Vertical->addItem(Horizental);
    Vertical->addWidget(EndTurn_Button,3,0);
    Vertical->addWidget(EndGame_Button,4,0);
    Vertical->addWidget(error,5,0);
    this->setLayout(Vertical);
    //this->resize(400, 400);

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
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    /**
     * removes disable on throwing dice button
     */
    timer1 = new QTimer();
    timer1->start(100);
    connect(timer1, SIGNAL(timeout()), this, SLOT(reveal()));





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
    ThrowBlue_Button->setEnabled(false);
    this->EndTurn_Button->setEnabled(true);
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

    bool iserror = false;


    if(blue->text() == "blue")
    {
        error->setText("Roll Dice First!");
        timer->start(4000);
        iserror = true;
    }
    else if(!blue->isChecked() && !red->isChecked())
    {
        error->setText("Please choose which die you want first!");
        timer->start(4000);
        iserror = true;
    }
    else if (blue->isChecked())
    {
        Game1Scene->Move(Game1Scene->player1, blueval);
        Game1Scene->Move(Game1Scene->player2, redval);
        //Game1Scene->player2->setPos(Game1Scene->player2->x(), Game1Scene->player2->y() - 30);
    }
    else if (red->isChecked())
    {
        Game1Scene->Move(Game1Scene->player1, redval);
        Game1Scene->Move(Game1Scene->player2, blueval);
        //Game1Scene->player2->setPos(Game1Scene->player2->x(), Game1Scene->player2->y() - 30);
    }




    if(iserror == false)
    {
    error->setText("Player 1 cell: " + QString::number(Game1Scene->player1->cell + 1) + "\n" + "Player 2 cell: " + QString::number(Game1Scene->player2->cell + 1));
    EndTurn_Button->setEnabled(false);
    this->ThrowBlue_Button->setEnabled(true);
    }





}

void dice :: SetUser (QString d, QString n)
{
    this->user = d;
    this->name = n;
    PlayerUsername->setText("Player " + name);
}

void dice :: reveal ()
{
    if (Game1Scene->player1->active == false && Game1Scene->player2->active == false)
    {
        Game1Scene->check(Game1Scene->player1);
        Game1Scene->check(Game1Scene->player2);



    }


}




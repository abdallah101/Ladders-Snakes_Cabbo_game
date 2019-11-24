#include "game2details.h"
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
#include <starter.h>
#include <winlose.h>
#include <QProgressBar>
using namespace std;
/**
  *\file game2details.cpp
  */
game2details::game2details(QWidget *parent) :
    QWidget(parent)
{
    QString s = "You can make one of the following possible actions:\n";
    s += "\n1. Pick up the top card from the discard pile and replace, face down, one of your cards or matching cards.\n";
    s += "\n2. Pick up the top card from the draw pile, look at it and do one of the following:\n";
    s += "(a) replace, face down, one of your cards or matching cards.\n";
    s += "(b) discard it.\n";
    s += "(c) if it's a choice card, carry out the action and then discard it.\n";
    s += "\n3. Call Cabo when you believe that you have the fewest points.\n";

    G2_Actions = new QLabel(s);
    G2_EndTurn = new QPushButton("I end my turn");
    G2_TurnOf = new QLabel("");
    G2_H = new QGridLayout;
    G2_H->addWidget(G2_Actions, 0, 0);
    G2_H->addWidget(G2_TurnOf, 1, 0);
    G2_H->addWidget(G2_EndTurn, 2, 0);
    this->setLayout(G2_H);

    PlayerTurn(1);
    this->resize(400,400);
    //this->setGeometry(0,400, 0,400);
    this->show();
}

/**
 * @brief PlayerTurn displays which player is about to play now
 * @param x is the number of the player whose turn is about to start
 */
void game2details::PlayerTurn(int x)
{
     QString sx = "Turn of player: ";
     sx += (x+'0');
     G2_TurnOf->setText(sx);
}




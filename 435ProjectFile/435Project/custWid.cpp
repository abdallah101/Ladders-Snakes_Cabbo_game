#include "custWid.h"
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
#include <QWidget>
#include <dice.h>

/**
  *\file custWid.cpp
  */

custWid::custWid(QWidget *parent) :
    QWidget(parent)
{
    /**
     * Creating buttons, input boxes, and Labels
     */
    Submit = new QPushButton("Submit");
    Done = new QPushButton("Done");
    ReadFromText = new QPushButton("ReadFromText");
    InsertText = new QDialogButtonBox();
    from = new QSpinBox(),to = new QSpinBox();
    Ladder = new QRadioButton("Ladder"), Snake = new QRadioButton("Snake");
    fromL = new QLabel("From");
    toL = new QLabel("To");


    /**
     * Signal connector to enter the position of a snake or a ladder
     */
    QObject::connect(Submit, SIGNAL(clicked()), this, SLOT(SubmitFunction()) );

    /**
     * Signal connector to a new customized game
     */
    QObject::connect(Done, SIGNAL(clicked()), this, SLOT(DoneFunction()) );

    /**
     * Signal connector to fill the grid
     */
    QObject::connect(ReadFromText , SIGNAL(clicked()), this, SLOT(FillGrid()) );

    /**
     * setting up the layout
     */

    custVertical = new QVBoxLayout();
    custHorizontal1 = new QGridLayout();
    custHorizontal2 = new QGridLayout();
    custHorizontal3 = new QGridLayout();
    custHorizontal4 = new QGridLayout();

    custHorizontal1->addWidget(Ladder, 0, 0);
    custHorizontal1->addWidget(Snake, 1, 0);

    custHorizontal2->addWidget(fromL, 0, 0);
    custHorizontal2->addWidget(from, 0, 1);
    custHorizontal2->addWidget(toL, 1, 0);
    custHorizontal2->addWidget(to, 1, 1);


    custHorizontal3->addWidget(Submit, 0, 0);
    custHorizontal4->addWidget(Done, 0, 0);
    custHorizontal4->addWidget(ReadFromText, 1, 0);

    custVertical->addItem(custHorizontal1);
    custVertical->addItem(custHorizontal2);
    custVertical->addItem(custHorizontal3);
    custVertical->addItem(custHorizontal4);

    this->setLayout(custVertical);
    this->resize(200, 200);

    sceneCust = new diceCust();


}

void custWid::SubmitFunction()
{
    sceneCust->Game1Cust->AddLadderSnake(from->text().toInt(), to->text().toInt());
}

void custWid::DoneFunction()
{
    this->close();
    sceneCust->show();
    sceneCust->Game1_ViewCust->show();
}

void custWid:: FillGrid()
{

    /**
     * saves the path to a .txt file that a user is promted to give
     */

    QString textPath = QFileDialog::getOpenFileName(this,tr("UserText"),"", tr("TEXT (*.txt)" ) );
    QFile file(textPath);
    file.open(QIODevice::ReadOnly);
    QDataStream inData(&file);

    while(!inData.atEnd())
    {
        qint32 x, y;
        inData >> x >> y;
        sceneCust->Game1Cust->gridCust[x-1] = y - 1;
    }
    file.close();
}

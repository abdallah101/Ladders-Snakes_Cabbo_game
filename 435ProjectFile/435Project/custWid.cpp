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
#include <QPixmap>
#include <snakesladders.h>
#include <tgmath.h>
#include <QString>
#include <iostream>
#include <string.h>

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
    error = new QLabel();

    /**
     * Signal connector to enter the position of a snake or a ladder
     */

    QObject::connect(Submit, SIGNAL(clicked()), this, SLOT(SubmitF()) );

    /**
     * Signal connector to a new customized game
     */
    QObject::connect(Done, SIGNAL(clicked()), this, SLOT(DoneFunction()) );

    /**
     * Signal connector to fill the grid
     */
    QObject::connect(ReadFromText , SIGNAL(clicked()), this, SLOT(FillGrid()) );

    /**
     * removes message after 4 seconds
     */
     timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));


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
    custVertical->addWidget(error);

    this->setLayout(custVertical);
    this->resize(200, 200);

    sceneCust = new dice();
    QImage green;
    if (green.load(QDir::currentPath() + "/Images/grid.PNG"))
    {
        sceneCust->Game1Scene->setBackgroundBrush(QBrush(green.scaledToHeight(612).scaledToWidth(612)));
    }

    error->setText("No vertical ladders or Snakes\nLadders only from down to up\nSnakes only from up to down");


}

void custWid::SubmitFunction()
{
    if(!Ladder->isChecked() && !Snake->isChecked())
    {
        error->setText("check if snake or ladder first");
    }
    else if (Ladder->isChecked())
    {

        int levelfrom, levelto, path, height; //path is the number of boxes from the "from tile" to the tile above it at the level of "to tile"
        levelfrom = ceil(from->text().toInt()/10.0); //gets level of the starting point
        levelto = ceil(to->text().toInt()/10.0); //gets level of ending point

        height = abs(levelfrom - levelto);  //gives height between starting and ending level


        //path is the number of the box above the starting box at the level of the ending box
        //path helps us know if the ending box is at the left or right of the starting box so that we know
        //if we should use left to right or right to left ladder or snake

        if(levelfrom%2==0 && levelto%2!=0)
        {

            if(from->text().toInt()%10 == 0)
            {
                path = levelto*10 - 9;
            }
            else
            {
                path = levelto*10 - (from->text().toInt()%10 - 1);
            }

        }
        else if (levelfrom%2!=0 && levelto%2==0)
        {
            if(from->text().toInt()%10 == 0)
            {
                path = levelto*10 - (9);
            }
            else
            {
                path = levelto*10 - (from->text().toInt()%10 - 1);
            }
        }
        else
        {
            path = from->text().toInt() + height*10;
        }



        if(levelto%2==0)  //if ending level is even
        {
            if(path > to->text().toInt()) //left to right
            {

                if(levelfrom%2==0)
                {
                    int x;
                    x = 10 - from->text().toInt()%10;

                    if(x == 10)
                    {
                        x = 0;
                    }

                    SnakesLadders * SL = new SnakesLadders();
                    SL->setPixmap(QPixmap(QDir::currentPath() + "/Images/ladderLR.png").scaled((abs(to->text().toDouble()-path))*61.2,height*61.2));

                    SL->setX(x*61.2 + 30.6);
                    SL->setY((10 - ceil(path/10.0))*61.2 + 30.6);

                    sceneCust->Game1Scene->addItem(SL);

                    sceneCust->Game1Scene->AddLadderSnake(from->text().toInt(), to->text().toInt());
                }
                else
                {

                    int x;
                    x = from->text().toInt()%10 - 1;

                    if(x == -1)
                    {
                        x = 9;
                    }

                    SnakesLadders * SL = new SnakesLadders();
                    SL->setPixmap(QPixmap(QDir::currentPath() + "/Images/ladderLR.png").scaled((abs(to->text().toDouble()-path))*61.2,height*61.2));

                    SL->setX(x*61.2 + 30.6);
                    SL->setY((10 - ceil(path/10.0))*61.2 + 30.6);

                    sceneCust->Game1Scene->addItem(SL);

                    sceneCust->Game1Scene->AddLadderSnake(from->text().toInt(), to->text().toInt());
                }

            }
            else if (path < to->text().toInt())
            {
                //right to left
                if(levelto%2==0)
                {
                    int x;
                    x = 10 - to->text().toInt()%10;

                    if(x == 10)
                    {
                        x = 0;
                    }

                    SnakesLadders * SL = new SnakesLadders();
                    SL->setPixmap(QPixmap(QDir::currentPath() + "/Images/ladderRL.png").scaled((abs(to->text().toDouble()-path))*61.2,height*61.2));

                    SL->setX(x*61.2 + 30.6);
                    SL->setY((10 - ceil(to->text().toInt()/10.0))*61.2 + 30.6);

                    sceneCust->Game1Scene->addItem(SL);

                    sceneCust->Game1Scene->AddLadderSnake(from->text().toInt(), to->text().toInt());
                }
                else
                {

                    int x;
                    x = to->text().toInt()%10 - 1;

                    if(x == -1)
                    {
                        x = 9;
                    }

                    SnakesLadders * SL = new SnakesLadders();
                    SL->setPixmap(QPixmap(QDir::currentPath() + "/Images/ladderRL.png").scaled((abs(to->text().toDouble()-path))*61.2,height*61.2));

                    SL->setX(x*61.2 + 30.6);
                    SL->setY((10 - ceil(to->text().toInt()/10.0))*61.2 + 30.6);

                    sceneCust->Game1Scene->addItem(SL);

                    sceneCust->Game1Scene->AddLadderSnake(from->text().toInt(), to->text().toInt());
                }

            }
            else if (path == to->text().toInt()) //vertical ladder, use image called LadderUP.png
            {
                if(levelto%2==0)
                {
                    int x;
                    x = 10 - to->text().toInt()%10;

                    if(x == 10)
                    {
                        x = 0;
                    }

                    SnakesLadders * SL = new SnakesLadders();
                    SL->setPixmap(QPixmap(QDir::currentPath() + "/Images/LadderUP.png").scaled(200,height*61.2));

                    SL->setX((x-1)*61.2);
                    SL->setY((10 - ceil(to->text().toInt()/10.0))*61.2 + 30.6);

                    sceneCust->Game1Scene->addItem(SL);

                    sceneCust->Game1Scene->AddLadderSnake(from->text().toInt(), to->text().toInt());
                }
                else
                {

                    int x;
                    x = to->text().toInt()%10 - 1;

                    if(x == -1)
                    {
                        x = 9;
                    }

                    SnakesLadders * SL = new SnakesLadders();
                    SL->setPixmap(QPixmap(QDir::currentPath() + "/Images/LadderUP.png").scaled(200,height*61.2));

                    SL->setX((x-1)*61.2);
                    SL->setY((10 - ceil(to->text().toInt()/10.0))*61.2 + 30.6);

                    sceneCust->Game1Scene->addItem(SL);

                    sceneCust->Game1Scene->AddLadderSnake(from->text().toInt(), to->text().toInt());
                }
            }
        }
        else  //if ending level is odd
        {
            if(path > to->text().toInt())
            {
                //right to left
                if(levelto%2==0)
                {
                    int x;
                    x = 10 - to->text().toInt()%10;

                    if(x == 10)
                    {
                        x = 0;
                    }

                    SnakesLadders * SL = new SnakesLadders();
                    SL->setPixmap(QPixmap(QDir::currentPath() + "/Images/ladderRL.png").scaled((abs(to->text().toDouble()-path))*61.2,height*61.2));

                    SL->setX(x*61.2 + 30.6);
                    SL->setY((10 - ceil(to->text().toInt()/10.0))*61.2 + 30.6);

                    sceneCust->Game1Scene->addItem(SL);

                    sceneCust->Game1Scene->AddLadderSnake(from->text().toInt(), to->text().toInt());
                }
                else
                {

                    int x;
                    x = to->text().toInt()%10 - 1;

                    if(x == -1)
                    {
                        x = 9;
                    }

                    SnakesLadders * SL = new SnakesLadders();
                    SL->setPixmap(QPixmap(QDir::currentPath() + "/Images/ladderRL.png").scaled((abs(to->text().toDouble()-path))*61.2,height*61.2));

                    SL->setX(x*61.2 + 30.6);
                    SL->setY((10 - ceil(to->text().toInt()/10.0))*61.2 + 30.6);

                    sceneCust->Game1Scene->addItem(SL);

                    sceneCust->Game1Scene->AddLadderSnake(from->text().toInt(), to->text().toInt());
                }

            }
            else if (path < to->text().toInt())
            {
               //left to right
                if(levelfrom%2==0)
                {
                    int x;
                    x = 10 - from->text().toInt()%10;

                    if(x == 10)
                    {
                        x = 0;
                    }

                    SnakesLadders * SL = new SnakesLadders();
                    SL->setPixmap(QPixmap(QDir::currentPath() + "/Images/ladderLR.png").scaled((abs(to->text().toDouble()-path))*61.2,height*61.2));

                    SL->setX(x*61.2 + 30.6);
                    SL->setY((10 - ceil(path/10.0))*61.2 + 30.6);

                    sceneCust->Game1Scene->addItem(SL);

                    sceneCust->Game1Scene->AddLadderSnake(from->text().toInt(), to->text().toInt());
                }
                else
                {

                    int x;
                    x = from->text().toInt()%10 - 1;

                    if(x == -1)
                    {
                        x = 9;
                    }

                    SnakesLadders * SL = new SnakesLadders();
                    SL->setPixmap(QPixmap(QDir::currentPath() + "/Images/ladderLR.png").scaled((abs(to->text().toDouble()-path))*61.2,height*61.2));

                    SL->setX(x*61.2 + 30.6);
                    SL->setY((10 - ceil(path/10.0))*61.2 + 30.6);

                    sceneCust->Game1Scene->addItem(SL);

                    sceneCust->Game1Scene->AddLadderSnake(from->text().toInt(), to->text().toInt());
                }


            }
            else if (path == to->text().toInt()) //vertical ladder, use LadderUP.png
            {
                if(levelfrom%2==0)
                {
                    int x;
                    x = 10 - from->text().toInt()%10;

                    if(x == 10)
                    {
                        x = 0;
                    }

                    SnakesLadders * SL = new SnakesLadders();
                    SL->setPixmap(QPixmap(QDir::currentPath() + "/Images/LadderUP.png").scaled(200,height*61.2));

                    SL->setX((x-1)*61.2);
                    SL->setY((10 - ceil(path/10.0))*61.2 + 30.6);

                    sceneCust->Game1Scene->addItem(SL);

                    sceneCust->Game1Scene->AddLadderSnake(from->text().toInt(), to->text().toInt());
                }
                else
                {

                    int x;
                    x = from->text().toInt()%10 - 1;

                    if(x == -1)
                    {
                        x = 9;
                    }

                    SnakesLadders * SL = new SnakesLadders();
                    SL->setPixmap(QPixmap(QDir::currentPath() + "/Images/LadderUP.png").scaled(200,height*61.2));

                    SL->setX((x-1)*61.2);
                    SL->setY((10 - ceil(path/10.0))*61.2 + 30.6);

                    sceneCust->Game1Scene->addItem(SL);

                    sceneCust->Game1Scene->AddLadderSnake(from->text().toInt(), to->text().toInt());
                }
            }
        }

    }
    else if (Snake->isChecked())
    {
        int levelfrom, levelto, path, height; //path is the number of boxes from the "from tile" to the tile above it at the level of "to tile"
        levelto = ceil(from->text().toInt()/10.0);
        levelfrom = ceil(to->text().toInt()/10.0);

        if(levelfrom > levelto)
        {
            height = levelfrom - levelto;
        }
        else
        {
            height = levelto - levelfrom;
        }

        if(levelfrom%2==0 && levelto%2!=0)
        {

            if(to->text().toInt()%10 == 0)
            {
                path = levelto*10 - 9;
            }
            else
            {
                path = levelto*10 - (to->text().toInt()%10 - 1);
            }

        }
        else if (levelfrom%2!=0 && levelto%2==0)
        {
            if(to->text().toInt()%10 == 0)
            {
                path = levelto*10 - (9);
            }
            else
            {
                path = levelto*10 - (to->text().toInt()%10 - 1);
            }
        }
        else
        {
            path = to->text().toInt() + height*10;
        }

        if(levelto%2==0)
        {
            if(path > from->text().toInt())
            {
                //left to right
                if(levelfrom%2==0)
                {
                    int x;
                    x = 10 - to->text().toInt()%10;

                    if(x == 10)
                    {
                        x = 0;
                    }

                    SnakesLadders * SL = new SnakesLadders();
                    SL->setPixmap(QPixmap(QDir::currentPath() + "/Images/snakeLR.png").scaled((abs(from->text().toDouble()-path))*61.2,height*61.2));

                    SL->setX(x*61.2 + 30.6);
                    SL->setY((10 - ceil(path/10.0))*61.2 + 30.6);

                    sceneCust->Game1Scene->addItem(SL);

                    sceneCust->Game1Scene->AddLadderSnake(from->text().toInt(), to->text().toInt());
                }
                else
                {

                    int x;
                    x = to->text().toInt()%10 - 1;

                    if(x == -1)
                    {
                        x = 9;
                    }

                    SnakesLadders * SL = new SnakesLadders();
                    SL->setPixmap(QPixmap(QDir::currentPath() + "/Images/snakeLR.png").scaled((abs(from->text().toDouble()-path))*61.2,height*61.2));

                    SL->setX(x*61.2 + 30.6);
                    SL->setY((10 - ceil(path/10.0))*61.2 + 30.6);

                    sceneCust->Game1Scene->addItem(SL);

                    sceneCust->Game1Scene->AddLadderSnake(from->text().toInt(), to->text().toInt());
                }

            }
            else if (path < from->text().toInt())
            {
                //right to left
                if(levelto%2==0)
                {
                    int x;
                    x = 10 - from->text().toInt()%10;

                    if(x == 10)
                    {
                        x = 0;
                    }

                    SnakesLadders * SL = new SnakesLadders();
                    SL->setPixmap(QPixmap(QDir::currentPath() + "/Images/snakeRL.png").scaled((abs(from->text().toDouble()-path))*61.2,height*61.2));

                    SL->setX(x*61.2 + 30.6);
                    SL->setY((10 - ceil(from->text().toInt()/10.0))*61.2 + 30.6);

                    sceneCust->Game1Scene->addItem(SL);

                    sceneCust->Game1Scene->AddLadderSnake(from->text().toInt(), to->text().toInt());
                }
                else
                {

                    int x;
                    x = from->text().toInt()%10 - 1;

                    if(x == -1)
                    {
                        x = 9;
                    }

                    SnakesLadders * SL = new SnakesLadders();
                    SL->setPixmap(QPixmap(QDir::currentPath() + "/Images/snakeRL.png").scaled((abs(from->text().toDouble()-path))*61.2,height*61.2));

                    SL->setX(x*61.2 + 30.6);
                    SL->setY((10 - ceil(from->text().toInt()/10.0))*61.2 + 30.6);

                    sceneCust->Game1Scene->addItem(SL);

                    sceneCust->Game1Scene->AddLadderSnake(from->text().toInt(), to->text().toInt());
                }

            }
            else if (path == from->text().toInt())
            {
                if(levelto%2==0)
                {
                    int x;
                    x = 10 - from->text().toInt()%10;

                    if(x == 10)
                    {
                        x = 0;
                    }

                    SnakesLadders * SL = new SnakesLadders();
                    SL->setPixmap(QPixmap(QDir::currentPath() + "/Images/SnakeUP.png").scaled(61.2,height*61.2));

                    SL->setX(x*61.2);
                    SL->setY((10 - ceil(from->text().toInt()/10.0))*61.2 + 30.6);

                    sceneCust->Game1Scene->addItem(SL);

                    sceneCust->Game1Scene->AddLadderSnake(from->text().toInt(), to->text().toInt());
                }
                else
                {

                    int x;
                    x = from->text().toInt()%10 - 1;

                    if(x == -1)
                    {
                        x = 9;
                    }

                    SnakesLadders * SL = new SnakesLadders();
                    SL->setPixmap(QPixmap(QDir::currentPath() + "/Images/SnakeUP.png").scaled(61.2,height*61.2));

                    SL->setX(x*61.2);
                    SL->setY((10 - ceil(from->text().toInt()/10.0))*61.2 + 30.6);

                    sceneCust->Game1Scene->addItem(SL);

                    sceneCust->Game1Scene->AddLadderSnake(from->text().toInt(), to->text().toInt());
                }
            }
        }
        else
        {
            if(path > from->text().toInt())
            {
                //right to left
                if(levelto%2==0)
                {
                    int x;
                    x = 10 - from->text().toInt()%10;

                    if(x == 10)
                    {
                        x = 0;
                    }

                    SnakesLadders * SL = new SnakesLadders();
                    SL->setPixmap(QPixmap(QDir::currentPath() + "/Images/snakeRL.png").scaled((abs(from->text().toDouble()-path))*61.2,height*61.2));

                    SL->setX(x*61.2 + 30.6);
                    SL->setY((10 - ceil(from->text().toInt()/10.0))*61.2 + 30.6);

                    sceneCust->Game1Scene->addItem(SL);

                    sceneCust->Game1Scene->AddLadderSnake(from->text().toInt(), to->text().toInt());
                }
                else
                {

                    int x;
                    x = from->text().toInt()%10 - 1;

                    if(x == -1)
                    {
                        x = 9;
                    }

                    SnakesLadders * SL = new SnakesLadders();
                    SL->setPixmap(QPixmap(QDir::currentPath() + "/Images/snakeRL.png").scaled((abs(from->text().toDouble()-path))*61.2,height*61.2));

                    SL->setX(x*61.2 + 30.6);
                    SL->setY((10 - ceil(from->text().toInt()/10.0))*61.2 + 30.6);

                    sceneCust->Game1Scene->addItem(SL);

                    sceneCust->Game1Scene->AddLadderSnake(from->text().toInt(), to->text().toInt());
                }

            }
            else if (path < from->text().toInt())
            {
               //left to right
                if(levelfrom%2==0)
                {
                    int x;
                    x = 10 - to->text().toInt()%10;

                    if(x == 10)
                    {
                        x = 0;
                    }

                    SnakesLadders * SL = new SnakesLadders();
                    SL->setPixmap(QPixmap(QDir::currentPath() + "/Images/snakeLR.png").scaled((abs(from->text().toDouble()-path))*61.2,height*61.2));

                    SL->setX(x*61.2 + 30.6);
                    SL->setY((10 - ceil(path/10.0))*61.2 + 30.6);

                    sceneCust->Game1Scene->addItem(SL);

                    sceneCust->Game1Scene->AddLadderSnake(from->text().toInt(), to->text().toInt());
                }
                else
                {

                    int x;
                    x = to->text().toInt()%10 - 1;

                    if(x == -1)
                    {
                        x = 9;
                    }

                    SnakesLadders * SL = new SnakesLadders();
                    SL->setPixmap(QPixmap(QDir::currentPath() + "/Images/snakeLR.png").scaled((abs(from->text().toDouble()-path))*61.2,height*61.2));

                    SL->setX(x*61.2 + 30.6);
                    SL->setY((10 - ceil(path/10.0))*61.2 + 30.6);

                    sceneCust->Game1Scene->addItem(SL);

                    sceneCust->Game1Scene->AddLadderSnake(from->text().toInt(), to->text().toInt());
                }


            }
            else if (path == from->text().toInt())
            {
                if(levelto%2==0)
                {
                    int x;
                    x = 10 - from->text().toInt()%10;

                    if(x == 10)
                    {
                        x = 0;
                    }

                    SnakesLadders * SL = new SnakesLadders();
                    SL->setPixmap(QPixmap(QDir::currentPath() + "/Images/SnakeUP.png").scaled(61.2,height*61.2));

                    SL->setX(x*61.2);
                    SL->setY((10 - ceil(from->text().toInt()/10.0))*61.2 + 30.6);

                    sceneCust->Game1Scene->addItem(SL);

                    sceneCust->Game1Scene->AddLadderSnake(from->text().toInt(), to->text().toInt());
                }
                else
                {

                    int x;
                    x = from->text().toInt()%10 - 1;

                    if(x == -1)
                    {
                        x = 9;
                    }

                    SnakesLadders * SL = new SnakesLadders();
                    SL->setPixmap(QPixmap(QDir::currentPath() + "/Images/SnakeUP.png").scaled(61.2,height*61.2));

                    SL->setX(x*61.2);
                    SL->setY((10 - ceil(from->text().toInt()/10.0))*61.2 + 30.6);

                    sceneCust->Game1Scene->addItem(SL);

                    sceneCust->Game1Scene->AddLadderSnake(from->text().toInt(), to->text().toInt());
                }
            }
        }

    }


}

void custWid::DoneFunction()
{
    this->close();
    sceneCust->SetUser(this->user, this->name, this->difficulty, this->starterplayer, false, true);
    sceneCust->show();
    sceneCust->Game1_View->show();




}

void custWid:: FillGrid()
{

    /**
     * saves the path to a .txt file that a user is promted to give
     */

    QString textPath = QFileDialog::getOpenFileName(this,tr("UserText"),"", tr("TEXT (*.txt)" ) );

    QFile file(textPath);
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QRegExp rx("(\\,)"); //RegEx for ','
    QTextStream lite(&file);

    QString sp;
    QStringList query;


    while(!lite.atEnd())
    {
        sp = lite.readLine();
        query = sp.split(rx);

        if(query[0] == "l")
        {
            int levelfrom, levelto, path, height; //path is the number of boxes from the "from tile" to the tile above it at the level of "to tile"
            from->setValue(query[1].toInt());
            to->setValue(query[2].toInt());
            levelfrom = ceil(from->text().toInt()/10.0);
            levelto = ceil(to->text().toInt()/10.0);

            if(levelfrom > levelto)
            {
                height = levelfrom - levelto;
            }
            else
            {
                height = levelto - levelfrom;
            }

            if(levelfrom%2==0 && levelto%2!=0)
            {

                if(from->text().toInt()%10 == 0)
                {
                    path = levelto*10 - 9;
                }
                else
                {
                    path = levelto*10 - (from->text().toInt()%10 - 1);
                }

            }
            else if (levelfrom%2!=0 && levelto%2==0)
            {
                if(from->text().toInt()%10 == 0)
                {
                    path = levelto*10 - (9);
                }
                else
                {
                    path = levelto*10 - (from->text().toInt()%10 - 1);
                }
            }
            else
            {
                path = from->text().toInt() + height*10;
            }

            if(levelto%2==0)
            {
                if(path > to->text().toInt())
                {
                    //left to right
                    if(levelfrom%2==0)
                    {
                        int x;
                        x = 10 - from->text().toInt()%10;

                        if(x == 10)
                        {
                            x = 0;
                        }

                        SnakesLadders * SL = new SnakesLadders();
                        SL->setPixmap(QPixmap(QDir::currentPath() + "/Images/ladderLR.png").scaled((abs(to->text().toDouble()-path))*61.2,height*61.2));

                        SL->setX(x*61.2 + 30.6);
                        SL->setY((10 - ceil(path/10.0))*61.2 + 30.6);

                        sceneCust->Game1Scene->addItem(SL);

                        sceneCust->Game1Scene->AddLadderSnake(from->text().toInt(), to->text().toInt());
                    }
                    else
                    {

                        int x;
                        x = from->text().toInt()%10 - 1;

                        if(x == -1)
                        {
                            x = 9;
                        }

                        SnakesLadders * SL = new SnakesLadders();
                        SL->setPixmap(QPixmap(QDir::currentPath() + "/Images/ladderLR.png").scaled((abs(to->text().toDouble()-path))*61.2,height*61.2));

                        SL->setX(x*61.2 + 30.6);
                        SL->setY((10 - ceil(path/10.0))*61.2 + 30.6);

                        sceneCust->Game1Scene->addItem(SL);

                        sceneCust->Game1Scene->AddLadderSnake(from->text().toInt(), to->text().toInt());
                    }

                }
                else
                {
                    //right to left
                    if(levelto%2==0)
                    {
                        int x;
                        x = 10 - to->text().toInt()%10;

                        if(x == 10)
                        {
                            x = 0;
                        }

                        SnakesLadders * SL = new SnakesLadders();
                        SL->setPixmap(QPixmap(QDir::currentPath() + "/Images/ladderRL.png").scaled((abs(to->text().toDouble()-path))*61.2,height*61.2));

                        SL->setX(x*61.2 + 30.6);
                        SL->setY((10 - ceil(to->text().toInt()/10.0))*61.2 + 30.6);

                        sceneCust->Game1Scene->addItem(SL);

                        sceneCust->Game1Scene->AddLadderSnake(from->text().toInt(), to->text().toInt());
                    }
                    else
                    {

                        int x;
                        x = to->text().toInt()%10 - 1;

                        if(x == -1)
                        {
                            x = 9;
                        }

                        SnakesLadders * SL = new SnakesLadders();
                        SL->setPixmap(QPixmap(QDir::currentPath() + "/Images/ladderRL.png").scaled((abs(to->text().toDouble()-path))*61.2,height*61.2));

                        SL->setX(x*61.2 + 30.6);
                        SL->setY((10 - ceil(to->text().toInt()/10.0))*61.2 + 30.6);

                        sceneCust->Game1Scene->addItem(SL);

                        sceneCust->Game1Scene->AddLadderSnake(from->text().toInt(), to->text().toInt());
                    }

                }
            }
            else
            {
                if(path > to->text().toInt())
                {
                    //right to left
                    if(levelto%2==0)
                    {
                        int x;
                        x = 10 - to->text().toInt()%10;

                        if(x == 10)
                        {
                            x = 0;
                        }

                        SnakesLadders * SL = new SnakesLadders();
                        SL->setPixmap(QPixmap(QDir::currentPath() + "/Images/ladderRL.png").scaled((abs(to->text().toDouble()-path))*61.2,height*61.2));

                        SL->setX(x*61.2 + 30.6);
                        SL->setY((10 - ceil(to->text().toInt()/10.0))*61.2 + 30.6);

                        sceneCust->Game1Scene->addItem(SL);

                        sceneCust->Game1Scene->AddLadderSnake(from->text().toInt(), to->text().toInt());
                    }
                    else
                    {

                        int x;
                        x = to->text().toInt()%10 - 1;

                        if(x == -1)
                        {
                            x = 9;
                        }

                        SnakesLadders * SL = new SnakesLadders();
                        SL->setPixmap(QPixmap(QDir::currentPath() + "/Images/ladderRL.png").scaled((abs(to->text().toDouble()-path))*61.2,height*61.2));

                        SL->setX(x*61.2 + 30.6);
                        SL->setY((10 - ceil(to->text().toInt()/10.0))*61.2 + 30.6);

                        sceneCust->Game1Scene->addItem(SL);

                        sceneCust->Game1Scene->AddLadderSnake(from->text().toInt(), to->text().toInt());
                    }

                }
                else
                {
                   //left to right
                    if(levelfrom%2==0)
                    {
                        int x;
                        x = 10 - from->text().toInt()%10;

                        if(x == 10)
                        {
                            x = 0;
                        }

                        SnakesLadders * SL = new SnakesLadders();
                        SL->setPixmap(QPixmap(QDir::currentPath() + "/Images/ladderLR.png").scaled((abs(to->text().toDouble()-path))*61.2,height*61.2));

                        SL->setX(x*61.2 + 30.6);
                        SL->setY((10 - ceil(path/10.0))*61.2 + 30.6);

                        sceneCust->Game1Scene->addItem(SL);

                        sceneCust->Game1Scene->AddLadderSnake(from->text().toInt(), to->text().toInt());
                    }
                    else
                    {

                        int x;
                        x = from->text().toInt()%10 - 1;

                        if(x == -1)
                        {
                            x = 9;
                        }

                        SnakesLadders * SL = new SnakesLadders();
                        SL->setPixmap(QPixmap(QDir::currentPath() + "/Images/ladderLR.png").scaled((abs(to->text().toDouble()-path))*61.2,height*61.2));

                        SL->setX(x*61.2 + 30.6);
                        SL->setY((10 - ceil(path/10.0))*61.2 + 30.6);

                        sceneCust->Game1Scene->addItem(SL);

                        sceneCust->Game1Scene->AddLadderSnake(from->text().toInt(), to->text().toInt());
                    }


                }
            }
        }
        else if ( query[0] == "s")
        {
            int levelfrom, levelto, path, height; //path is the number of boxes from the "from tile" to the tile above it at the level of "to tile"
            from->setValue(query[1].toInt());
            to->setValue(query[2].toInt());

            levelto = ceil(from->text().toInt()/10.0);
            levelfrom = ceil(to->text().toInt()/10.0);

            if(levelfrom > levelto)
            {
                height = levelfrom - levelto;
            }
            else
            {
                height = levelto - levelfrom;
            }

            if(levelfrom%2==0 && levelto%2!=0)
            {

                if(to->text().toInt()%10 == 0)
                {
                    path = levelto*10 - 9;
                }
                else
                {
                    path = levelto*10 - (to->text().toInt()%10 - 1);
                }

            }
            else if (levelfrom%2!=0 && levelto%2==0)
            {
                if(to->text().toInt()%10 == 0)
                {
                    path = levelto*10 - (9);
                }
                else
                {
                    path = levelto*10 - (to->text().toInt()%10 - 1);
                }
            }
            else
            {
                path = to->text().toInt() + height*10;
            }

            if(levelto%2==0)
            {
                if(path > from->text().toInt())
                {
                    //left to right
                    if(levelfrom%2==0)
                    {
                        int x;
                        x = 10 - to->text().toInt()%10;

                        if(x == 10)
                        {
                            x = 0;
                        }

                        SnakesLadders * SL = new SnakesLadders();
                        SL->setPixmap(QPixmap(QDir::currentPath() + "/Images/snakeLR.png").scaled((abs(from->text().toDouble()-path))*61.2,height*61.2));

                        SL->setX(x*61.2 + 30.6);
                        SL->setY((10 - ceil(path/10.0))*61.2 + 30.6);

                        sceneCust->Game1Scene->addItem(SL);

                        sceneCust->Game1Scene->AddLadderSnake(from->text().toInt(), to->text().toInt());
                    }
                    else
                    {

                        int x;
                        x = to->text().toInt()%10 - 1;

                        if(x == -1)
                        {
                            x = 9;
                        }

                        SnakesLadders * SL = new SnakesLadders();
                        SL->setPixmap(QPixmap(QDir::currentPath() + "/Images/snakeLR.png").scaled((abs(from->text().toDouble()-path))*61.2,height*61.2));

                        SL->setX(x*61.2 + 30.6);
                        SL->setY((10 - ceil(path/10.0))*61.2 + 30.6);

                        sceneCust->Game1Scene->addItem(SL);

                        sceneCust->Game1Scene->AddLadderSnake(from->text().toInt(), to->text().toInt());
                    }

                }
                else
                {
                    //right to left
                    if(levelto%2==0)
                    {
                        int x;
                        x = 10 - from->text().toInt()%10;

                        if(x == 10)
                        {
                            x = 0;
                        }

                        SnakesLadders * SL = new SnakesLadders();
                        SL->setPixmap(QPixmap(QDir::currentPath() + "/Images/snakeRL.png").scaled((abs(from->text().toDouble()-path))*61.2,height*61.2));

                        SL->setX(x*61.2 + 30.6);
                        SL->setY((10 - ceil(from->text().toInt()/10.0))*61.2 + 30.6);

                        sceneCust->Game1Scene->addItem(SL);

                        sceneCust->Game1Scene->AddLadderSnake(from->text().toInt(), to->text().toInt());
                    }
                    else
                    {

                        int x;
                        x = from->text().toInt()%10 - 1;

                        if(x == -1)
                        {
                            x = 9;
                        }

                        SnakesLadders * SL = new SnakesLadders();
                        SL->setPixmap(QPixmap(QDir::currentPath() + "/Images/snakeRL.png").scaled((abs(from->text().toDouble()-path))*61.2,height*61.2));

                        SL->setX(x*61.2 + 30.6);
                        SL->setY((10 - ceil(from->text().toInt()/10.0))*61.2 + 30.6);

                        sceneCust->Game1Scene->addItem(SL);

                        sceneCust->Game1Scene->AddLadderSnake(from->text().toInt(), to->text().toInt());
                    }

                }
            }
            else
            {
                if(path > from->text().toInt())
                {
                    //right to left
                    if(levelto%2==0)
                    {
                        int x;
                        x = 10 - from->text().toInt()%10;

                        if(x == 10)
                        {
                            x = 0;
                        }

                        SnakesLadders * SL = new SnakesLadders();
                        SL->setPixmap(QPixmap(QDir::currentPath() + "/Images/snakeRL.png").scaled((abs(from->text().toDouble()-path))*61.2,height*61.2));

                        SL->setX(x*61.2 + 30.6);
                        SL->setY((10 - ceil(from->text().toInt()/10.0))*61.2 + 30.6);

                        sceneCust->Game1Scene->addItem(SL);

                        sceneCust->Game1Scene->AddLadderSnake(from->text().toInt(), to->text().toInt());
                    }
                    else
                    {

                        int x;
                        x = from->text().toInt()%10 - 1;

                        if(x == -1)
                        {
                            x = 9;
                        }

                        SnakesLadders * SL = new SnakesLadders();
                        SL->setPixmap(QPixmap(QDir::currentPath() + "/Images/snakeRL.png").scaled((abs(from->text().toDouble()-path))*61.2,height*61.2));

                        SL->setX(x*61.2 + 30.6);
                        SL->setY((10 - ceil(from->text().toInt()/10.0))*61.2 + 30.6);

                        sceneCust->Game1Scene->addItem(SL);

                        sceneCust->Game1Scene->AddLadderSnake(from->text().toInt(), to->text().toInt());
                    }

                }
                else
                {
                   //left to right
                    if(levelfrom%2==0)
                    {
                        int x;
                        x = 10 - to->text().toInt()%10;

                        if(x == 10)
                        {
                            x = 0;
                        }

                        SnakesLadders * SL = new SnakesLadders();
                        SL->setPixmap(QPixmap(QDir::currentPath() + "/Images/snakeLR.png").scaled((abs(from->text().toDouble()-path))*61.2,height*61.2));

                        SL->setX(x*61.2 + 30.6);
                        SL->setY((10 - ceil(path/10.0))*61.2 + 30.6);

                        sceneCust->Game1Scene->addItem(SL);

                        sceneCust->Game1Scene->AddLadderSnake(from->text().toInt(), to->text().toInt());
                    }
                    else
                    {

                        int x;
                        x = to->text().toInt()%10 - 1;

                        if(x == -1)
                        {
                            x = 9;
                        }

                        SnakesLadders * SL = new SnakesLadders();
                        SL->setPixmap(QPixmap(QDir::currentPath() + "/Images/snakeLR.png").scaled((abs(from->text().toDouble()-path))*61.2,height*61.2));

                        SL->setX(x*61.2 + 30.6);
                        SL->setY((10 - ceil(path/10.0))*61.2 + 30.6);

                        sceneCust->Game1Scene->addItem(SL);

                        sceneCust->Game1Scene->AddLadderSnake(from->text().toInt(), to->text().toInt());
                    }


                }
            }
}
        else{}



    }

   /* while(!inData.atEnd())
    {
        qint32 x, y;
        inData >> x >> y;
        sceneCust->Game1Scene->gridCust[x-1] = y - 1;
    }*/

    file.close();

}

void custWid :: update()
{
    error->setText("No vertical ladders or Snakes\nLadders only from down to up\nSnakes only from up to down");
}

void custWid :: SetUser(QString d, QString a, int diff, int s)
{
    this->user = d;
    this->name = a;
    this->difficulty = diff;
    this->starterplayer = s;
}

void custWid:: SubmitF()
{
    int levelfrom, levelto, height;
    levelfrom = ceil(from->text().toInt()/10.0); //gets level of the starting point
    levelto = ceil(to->text().toInt()/10.0); //gets level of ending point

    height = abs(levelfrom - levelto);  //gives height between starting and ending level

    if(this->Ladder->isChecked())
    {
        if (this->from->text().toInt() > this->to->text().toInt() || height == 0)
        {
            error->setText("Impossible Ladder, try snake!");
            timer->start(4000);

        }
        else
        {
            SubmitFunction();
        }
    }
    if(this->Snake->isChecked())
    {
        if(this->from->text().toInt() < this->to->text().toInt() || height == 0)
        {
            error->setText("Impossible Snake, try ladder!");
            timer->start(4000);
        }
        else
        {
            SubmitFunction();

        }
    }
    if(this->Ladder->isChecked() == false && this->Snake->isChecked() == false)
    {
        error->setText("Choose a ladder or snake first!");
        timer->start(4000);
    }
}

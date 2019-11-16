#include "game1_scene.h"
#include <QApplication>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QWidget>
#include <QTimer>
#include <QFile>
#include <QPixmap>
#include <QImage>
#include <QDir>
#include <players.h>
#include <fstream>
#include <QFile>
#include <QDir>
#include <iostream>
#include <QTextStream>
#include <QRegularExpression>

/**
  *\file game1_scene.cpp
  * board logic
  */

game1_scene::game1_scene()
{


    /**
      *Initialize the grid of the game
      */
    for (int i=0;i<100; i++)
    {
        grid[i] = 0;
    }


    /*! \brief Scaling the background
     */

    /**
      * Setting background for scene
      */
    this->setSceneRect(0,0,612, 612);


    player1 = new players();
    player1->setPixmap((QPixmap(QDir::currentPath() + "/Images/yellow.png")).scaled(30,30));
    player2 = new players();

    /**
      * add 30 offset between player 1 and 2 to avoid overlap
      */

    player2->setPos(player2->x() , player2->y() - 30);
    player2->setPixmap((QPixmap(QDir::currentPath() + "/Images/purple.jpg")).scaled(30,30));
    this->addItem(player1);
    this->addItem(player2);




}


void game1_scene::Move(players * player, int steps)
{




if(isCust == false)
{
    //keep in mind throught the whole process that player1 always moves before player2 even if it is player 2's turn

    QFile data(QDir::currentPath() + "/history.txt");
        data.open(QIODevice::Text | QIODevice::ReadOnly);
        QString dataText = data.readAll();
        data.close();


    QFile file(QDir::currentPath() + "/history.txt");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QRegExp rx("(\\,)"); //RegEx for ','
    QTextStream lite(&file);
    QString sp;
    QStringList query;

    QString temp = ""; //this will copy all the history of the user to add to it then copy it back

    while(!lite.atEnd())
    {

        sp = lite.readLine();
        query = sp.split(rx);

        if(this->user == query[0])
        {
            break;
        }

    }

    file.close();

    for(int i = 0 ; i < query.size()-1 ; i++)
    {
        temp = temp  + query[i] + ",";
    }
    steps = steps + 1;
    QRegularExpression re(temp);

    int difficulty; //difficulty 1 -> -4 / 2 -> -5 / 3 -> -6 / 4 -> -7

    if(this->diff == 1)
    {
        difficulty = -4;
    }

    else if (this->diff == 2)
    {
        difficulty = -5;
    }
    else if (this->diff == 3)
    {
        difficulty = -6;
    }
    else if (this->diff == 4)
    {
        difficulty = -7;
    }

    if(query[1] == "-3") //-3 indicates that the account is still new (aka no history yet)
    {
        if(startingplayer == "-1") //-1 indicates that player 1 started
        {
            temp = user + ",-1," + QString::number(difficulty) + "," + QString::number(player->cell + steps) + ",";
            dataText.replace(re, temp);
        }
        else if ( startingplayer == "-2") //else -2 indicates that player 2 started
        {
             temp = user + ",-2," + QString::number(difficulty) + "," + QString::number(player->cell + steps) + ",";
            dataText.replace(re, temp);
        }
    }
    else
    {

        if(isResume == false)
        {
            if( query[query.size()-2] == "x" || query[query.size()-2] == "w" || query[query.size()-2] == "l")
            {
                if(startingplayer == "-1") //-1 indicates that the sequence is player1,player2,player1,player2....
                {
                    temp = temp + "-1," + QString::number(difficulty) + "," + QString::number(player->cell + steps) + ",";
                    dataText.replace(re, temp);
                }
                else if ( startingplayer == "-2") //else -2 indicates that the sequence is player2,player1,player2,player1....
                {
                    temp = temp + "-2," + QString::number(difficulty) + "," + QString::number(player->cell + steps) + ",";
                    dataText.replace(re, temp);
                }
            }
            else
            {
                temp = temp + QString::number(player->cell + steps) + ",";
                dataText.replace(re, temp);
            }

        }

        else //here player is playing a resumed game
        {

                temp = temp + QString::number(player->cell + steps) + ",";
                dataText.replace(re, temp);

        }

    }


    QFile newData(QDir::currentPath() + "/history.txt");
    data.resize(0);
    if(newData.open(QFile::WriteOnly | QFile::Truncate))
    {
        QTextStream out(&newData);
        out << dataText;
    }
    newData.close();

    steps = steps - 1;
}
else
{//here if the game is custom, to be implemented later if i ever feel like it ( I don't )
}

     player->MoveP(steps); //calls function that moves the player by steps




}

void game1_scene :: check (players * player)
{
    if (player->notFirst == true )//cause there is a ladder at the start
    {
        if(grid[player->cell] != 0) //checks for ladders or snakes and moves player accordingly
        {
            player->MovePExtra(grid[player->cell]);


            if(isCust == false)
            {
                QFile data(QDir::currentPath() + "/history.txt");
                    data.open(QIODevice::Text | QIODevice::ReadOnly);
                    QString dataText = data.readAll();
                    data.close();


                QFile file(QDir::currentPath() + "/history.txt");
                file.open(QIODevice::ReadOnly|QIODevice::Text);
                QRegExp rx("(\\,)"); //RegEx for ','
                QTextStream lite(&file);
                QString sp;
                QStringList query;

                QString temp = ""; //this will copy all the history of the user to add to it then copy it back

                while(!lite.atEnd())
                {

                    sp = lite.readLine();
                    query = sp.split(rx);

                    if(this->user == query[0])
                    {
                        break;
                    }

                }

                file.close();

                for(int i = 0 ; i < query.size()-1 ; i++)
                {
                    temp = temp  + query[i] + ",";
                }

                QRegularExpression re(temp);


                if(grid[player1->cell] != 0 && grid[player2->cell] != 0)
                {
                    temp = temp + QString::number(grid[player->cell]+1) + ",";
                }
                else
                {

                 if(grid[player1->cell] != 0)
                 {
                    temp = temp + QString::number(grid[player1->cell]+1) + ",";
                 }
                 else
                 {
                     temp = temp + QString::number(player1->cell+1) + ",";
                 }

                 if(grid[player2->cell] != 0)
                 {
                    temp = temp + QString::number(grid[player2->cell]+1) + ",";
                 }
                 else
                 {
                     temp = temp + QString::number(player2->cell+1) + ",";
                 }

                }

                dataText.replace(re,temp);


                QFile newData(QDir::currentPath() + "/history.txt");
                data.resize(0);
                if(newData.open(QFile::WriteOnly | QFile::Truncate))
                {
                    QTextStream out(&newData);
                    out << dataText;
                }
                newData.close();

            }
            else
            {
                //here is also for if the game is custom but for ladders and snakes part of history
            }




        }
    }
}

void game1_scene :: SetUser(QString a, QString b, int c, bool d, bool z)
{
    //to save history under the user's username
    this->user = a;
    this->startingplayer = b;
    this->diff = c;
    this->isResume = d;
    this->isCust = z;

    if(this->isCust == false)
    {
        grid[0] = 37;
        grid[3] = 13;
        grid[8] = 30;
        grid[20] = 41;
        grid[27] = 83;
        grid[50] = 66;
        grid[70] = 90;
        grid[79] = 99;
        grid[16] = 6;
        grid[61] = 18;
        grid[63] = 59;
        grid[53] = 33;
        grid[86] = 23;
        grid[92] = 72;
        grid[94] = 74;
        grid[97] = 78;

        QImage green;

        if (green.load(QDir::currentPath() + "/Images/SL.jpg"))
        {
            //green.scaledToWidth(this->width(), Qt::SmoothTransformation);
            //green.scaled(500,500);
            this->setBackgroundBrush(QBrush(green.scaledToHeight(612).scaledToWidth(612)));

        }
    }
    else
    {
        //this->setSceneRect(0,0,612, 612);
        QImage green;
        if (green.load(QDir::currentPath() + "/Images/grid.PNG"))
        {
            this->setBackgroundBrush(QBrush(green.scaledToHeight(612).scaledToWidth(612)));
        }



    }
}

void game1_scene::AddLadderSnake(int cellFrom, int cellTo)
{
    this->grid[cellFrom-1] = cellTo - 1;
}


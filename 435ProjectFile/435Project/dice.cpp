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
#include <starter.h>
#include <winlose.h>
using namespace std;
/**
  *\file dice.cpp
  */

dice::dice(QWidget *parent) :
    QWidget(parent)
{
    /**
     * Creating buttons, input boxes, and Labels
     */


    ThrowBlue_Button = new QPushButton("Throw dice");
    //ThrowRed_Button = new QPushButton("Throw red die");
    EndTurn_Button = new QPushButton("End Turn");
    EndGame_Button = new QPushButton("End Game");
    PlayerUsername = new QLabel("Player x");
    this->EndTurn_Button->setEnabled(false);
    blue = new QRadioButton("blue");
    red = new QRadioButton("red");
    Game1Scene = new game1_scene();
    Game1_View = new QGraphicsView();
    error = new QLabel("");
    VerticalRadioB = new QVBoxLayout();
    GP = new QGroupBox();
    choose = new QLabel("Choose!");

    /**
     * defining class variables
     */

    endedturn = false;
    endedturnPC = false;
    once = false;
    other = false;
    taketurns = false;

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
     * removes enable/disable on throwing dice button
     */
    timer1 = new QTimer();
    timer1->start(100);
    connect(timer1, SIGNAL(timeout()), this, SLOT(reveal()));

    /**
     * PC checks if its his turn and works accordingly
     */
    timerPC = new QTimer();
    timerPC->start(100);
    connect(timer1, SIGNAL(timeout()), this, SLOT(listener()));

    Game1_View->setScene(Game1Scene);
    Game1_View->setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    Game1_View->setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    Game1_View->show();





}

/**
 * \brief Function to throw both die for player1's turn
 * \param Takes no parameter
 * \return nothing (type: void)
 */

void dice :: ThrowBlue()
{


    //disables the throw button and enables the end turn button

    ThrowBlue_Button->setEnabled(false);

    //this->EndTurn_Button->setEnabled(true);
    endedturn = true;
    endedturnPC = false;
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
 * \brief Function to throw both die but for PC's turn
 * \param Takes no parameter
 * \return nothing (type: void)
 */

void dice :: ThrowBluePC()
{


    //disables the throw button and enables the end turn button
    //ThrowBlue_Button->setEnabled(false);
    //this->EndTurn_Button->setEnabled(true);
    //endedturn = true;

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
 * \brief Function that ends a game (behaviour is in closeevent function that overrides "x" button in dice widget)
 * \param Takes no parameter
 * \return nothing (type: void)
 */

void dice :: EndGame()
{

    this->close();

}

/**
 * \brief Function that ends a player's turn
 * \param Takes no parameter
 * \return nothing (type: void)
 */

void dice :: EndTurn()
{


    bool iserror = false;


    if(difficulty == 4) //this is when there are 2 human players, uses the checked radiobutto number to move for the player who its his current turn
    {
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
        if (other == false)
        {
        Game1Scene->Move(Game1Scene->player1, blueval);
        Game1Scene->Move(Game1Scene->player2, redval);
        //Game1Scene->player2->setPos(Game1Scene->player2->x(), Game1Scene->player2->y() - 30);
        error->setText("Player 1 cell: " + QString::number(Game1Scene->player1->cell + 1 + blueval) + "\n" + "Player 2 cell: " + QString::number(Game1Scene->player2->cell + 1 + redval));
        }
        else
        {
            Game1Scene->Move(Game1Scene->player1, redval);
            Game1Scene->Move(Game1Scene->player2, blueval);
            //Game1Scene->player2->setPos(Game1Scene->player2->x(), Game1Scene->player2->y() - 30);
            error->setText("Player 1 cell: " + QString::number(Game1Scene->player1->cell + 1 + redval) + "\n" + "Player 2 cell: " + QString::number(Game1Scene->player2->cell + 1 + blueval));
            }

    }
    else if (red->isChecked())
    {
        if(other == false)
        {
        Game1Scene->Move(Game1Scene->player1, redval);
        Game1Scene->Move(Game1Scene->player2, blueval);
        //Game1Scene->player2->setPos(Game1Scene->player2->x(), Game1Scene->player2->y() - 30);
        error->setText("Player 1 cell: " + QString::number(Game1Scene->player1->cell + 1 + redval) + "\n" + "Player 2 cell: " + QString::number(Game1Scene->player2->cell + 1 + blueval));
   }
        else
        {
            Game1Scene->Move(Game1Scene->player1, blueval);
            Game1Scene->Move(Game1Scene->player2, redval);
            //Game1Scene->player2->setPos(Game1Scene->player2->x(), Game1Scene->player2->y() - 30);
            error->setText("Player 1 cell: " + QString::number(Game1Scene->player1->cell + 1 + blueval) + "\n" + "Player 2 cell: " + QString::number(Game1Scene->player2->cell + 1 + redval));
            }
        }

}

    if(difficulty < 4) //if playing against the PC each player has an end turn function, check EndTurnPC for PC's version
    {
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
        error->setText("Player 1 cell: " + QString::number(Game1Scene->player1->cell + 1 + blueval) + "\n" + "Player 2 cell: " + QString::number(Game1Scene->player2->cell + 1 + redval));


    }
    else if (red->isChecked())
    {

            Game1Scene->Move(Game1Scene->player1, redval);
            Game1Scene->Move(Game1Scene->player2, blueval);
            //Game1Scene->player2->setPos(Game1Scene->player2->x(), Game1Scene->player2->y() - 30);
            error->setText("Player 1 cell: " + QString::number(Game1Scene->player1->cell + 1 + redval) + "\n" + "Player 2 cell: " + QString::number(Game1Scene->player2->cell + 1 + blueval));


    }
    }


    //if we are playing against PC then difficulty < 4 and need to switch between true and false for each players when ending turn
    if(iserror == false && difficulty < 4)
    {
        this->EndTurn_Button->setEnabled(false);
        //this->ThrowBlue_Button->setEnabled(false);
        endedturn = false;
        Game1Scene->player1->myturn = false;
        Game1Scene->player2->myturn = true;
    }
    //likewise when playing against a human (difficulty = 4) but using bool other
    else if  (iserror == false && difficulty == 4)
    {
        this->EndTurn_Button->setEnabled(false);
        this->ThrowBlue_Button->setEnabled(true);
        endedturn = false;

        if(other == false)
        {
            other = true;
        }
        else
        {
            other = false;
        }


    }

}

/**
 * \brief Function that ends a PC's turn
 * \param Takes no parameter
 * \return nothing (type: void)
 */

void dice :: EndTurnPC()
{

    if(difficulty == 1) //easy PC takes random number
    {
        srand(time(NULL));
        int x =1+ (rand()%2);

        if(x == 1)
        {
            Game1Scene->Move(Game1Scene->player1, redval);
            Game1Scene->Move(Game1Scene->player2, blueval);
            error->setText("Player 1 cell: " + QString::number(Game1Scene->player1->cell + 1 + redval) + "\n" + "Player 2 cell: " + QString::number(Game1Scene->player2->cell + 1 + blueval));
        }
        else
        {
            Game1Scene->Move(Game1Scene->player1, blueval);
            Game1Scene->Move(Game1Scene->player2, redval);
            error->setText("Player 1 cell: " + QString::number(Game1Scene->player1->cell + 1 + blueval) + "\n" + "Player 2 cell: " + QString::number(Game1Scene->player2->cell + 1 + redval));
        }
    }

    else if (difficulty == 2) //medium PC takes higher number
    {
        if(blueval >= redval)
        {
            Game1Scene->Move(Game1Scene->player1, redval);
            Game1Scene->Move(Game1Scene->player2, blueval);
            error->setText("Player 1 cell: " + QString::number(Game1Scene->player1->cell + 1 + redval) + "\n" + "Player 2 cell: " + QString::number(Game1Scene->player2->cell + 1 + blueval));
        }
        else
        {
            Game1Scene->Move(Game1Scene->player1, blueval);
            Game1Scene->Move(Game1Scene->player2, redval);
            error->setText("Player 1 cell: " + QString::number(Game1Scene->player1->cell + 1 + blueval) + "\n" + "Player 2 cell: " + QString::number(Game1Scene->player2->cell + 1 + redval));
        }
    }
    else if (difficulty == 3) //hard PC checks for ladders and snakes both for him and his opponent
    {
        int redPC = Game1Scene->player2->cell + redval;
        int bluePC = Game1Scene->player2->cell + blueval;
        int red = Game1Scene->player1->cell + redval;
        int blue = Game1Scene->player1->cell + blueval;

        if(Game1Scene->grid[redPC] != 0 && Game1Scene->grid[redPC] < redPC) //checks if snake for red value
        {
            if(Game1Scene->grid[bluePC] != 0 && Game1Scene->grid[bluePC] < bluePC) //checks if snake for blue value
            {
                //here both are snakes
                if(Game1Scene->grid[bluePC] < Game1Scene->grid[redPC]) //if both are snakes then check which is better
                {
                    Game1Scene->Move(Game1Scene->player1, blueval);
                    Game1Scene->Move(Game1Scene->player2, redval);

                }
                else
                {
                    Game1Scene->Move(Game1Scene->player1, redval);
                    Game1Scene->Move(Game1Scene->player2, blueval);
                }
            }
            else
            {
                //here red is snake so take blue
                Game1Scene->Move(Game1Scene->player1, redval);
                Game1Scene->Move(Game1Scene->player2, blueval);
            }
        }
        else
        {
            if(Game1Scene->grid[bluePC] != 0 && Game1Scene->grid[bluePC] < bluePC) //checks if snake for blue value
            {
                //here red is not snake, but if blue is snake then take red

                Game1Scene->Move(Game1Scene->player1, blueval);
                Game1Scene->Move(Game1Scene->player2, redval);
            }
            else
            {
                //here both aren't snakes
                //so check for ladders now
                if(Game1Scene->grid[bluePC] != 0 && Game1Scene->grid[bluePC] > bluePC) //checks blue for ladder
                {
                    if(Game1Scene->grid[redPC] != 0 && Game1Scene->grid[redPC] < redPC) //checks red for ladder
                    {
                        //here both are ladders
                        if(Game1Scene->grid[bluePC] < Game1Scene->grid[redPC]) //if both are ladders then check which is better
                        {

                            Game1Scene->Move(Game1Scene->player1, blueval);
                            Game1Scene->Move(Game1Scene->player2, redval);
                        }
                        else
                        {

                            Game1Scene->Move(Game1Scene->player1, redval);
                            Game1Scene->Move(Game1Scene->player2, blueval);
                        }
                    }
                }
                else
                {
                    //here blue isnt a ladder, check for red
                    if(Game1Scene->grid[redPC] != 0 && Game1Scene->grid[redPC] < redPC)
                    {

                        Game1Scene->Move(Game1Scene->player1, blueval);
                        Game1Scene->Move(Game1Scene->player2, redval);
                    }
                    else
                    {
                        //here redPC isnt a ladder and bluePC aren't ladders (and both aren't snakes)

                        if(Game1Scene->grid[red] != 0 && Game1Scene->grid[red] < red) //check if 2 goes to snake red
                        {
                            if(Game1Scene->grid[blue] != 0 && Game1Scene->grid[blue] < blue)
                            {
                                if(Game1Scene->grid[blue] < Game1Scene->grid[red])
                                {
                                    Game1Scene->Move(Game1Scene->player1, blueval);
                                    Game1Scene->Move(Game1Scene->player2, redval);
                                }
                                else
                                {
                                    Game1Scene->Move(Game1Scene->player1, redval);
                                    Game1Scene->Move(Game1Scene->player2, blueval);
                                }
                            }
                            else
                            {
                                Game1Scene->Move(Game1Scene->player1, redval);
                                Game1Scene->Move(Game1Scene->player2, blueval);
                            }
                        }
                        else
                        {
                            if(Game1Scene->grid[blue] != 0 && Game1Scene->grid[blue] < blue)
                            {
                                Game1Scene->Move(Game1Scene->player1, blueval);
                                Game1Scene->Move(Game1Scene->player2, redval);
                            }
                            else
                            {
                                //here red and blue dont take the other player to a snake so check for ladders
                                if(Game1Scene->grid[blue] != 0 && Game1Scene->grid[blue] > blue)
                                {
                                    if(Game1Scene->grid[red] != 0 && Game1Scene->grid[red] > red)
                                    {
                                        if(Game1Scene->grid[blue] < Game1Scene->grid[red])
                                        {
                                            Game1Scene->Move(Game1Scene->player1, blueval);
                                            Game1Scene->Move(Game1Scene->player2, redval);
                                        }
                                        else
                                        {
                                            Game1Scene->Move(Game1Scene->player1, redval);
                                            Game1Scene->Move(Game1Scene->player2, blueval);
                                        }
                                    }
                                    else
                                    {
                                        Game1Scene->Move(Game1Scene->player1, redval);
                                        Game1Scene->Move(Game1Scene->player2, blueval);
                                    }
                                }
                                else
                                {
                                    //here blue doesnt take him to ladder so check for red
                                    if(Game1Scene->grid[red] != 0 && Game1Scene->grid[red] > red)
                                    {
                                           Game1Scene->Move(Game1Scene->player1, blueval);
                                           Game1Scene->Move(Game1Scene->player2, redval);
                                    }
                                    else
                                    {
                                        //here player2 goes to neither a ladder nor a snake with any option
                                        //so just choose highest number
                                        if(redval > blueval)
                                        {
                                            Game1Scene->Move(Game1Scene->player1, blueval);
                                            Game1Scene->Move(Game1Scene->player2, redval);
                                        }
                                        else
                                        {
                                            Game1Scene->Move(Game1Scene->player1, redval);
                                            Game1Scene->Move(Game1Scene->player2, blueval);
                                        }
                                    }
                                }
                            }
                        }




                    }
                }
            }
        }
    }


    Game1Scene->player1->myturn = true;
    Game1Scene->player2->myturn = false;
    endedturnPC = true;




}

/**
 * \brief Function that sets up the game, defining the user and his name, the difficulty, who starts, and if the game is a resume
 * \param QString, QString, int, int, bool
 * \return nothing (type: void)
 */
void dice :: SetUser (QString d, QString n, int s, int w, bool h)
{
    //initialization passed from gameone class
    this->user = d;
    this->name = n;
    this->difficulty = s;
    this->startingPlayer = w;
    this->isResume = h;
    PlayerUsername->setText("Player " + name);

    //determining who starts the game
    if(startingPlayer == 1 && difficulty!=4)
    {
        PlayerUsername->setText("Player: " + name);
        Game1Scene->player1->myturn = true;
    }
    else if (startingPlayer == 2 && difficulty != 4)
    {
        PlayerUsername->setText("Player2(PC)");
        Game1Scene->player2->myturn = true;
        ThrowBlue_Button->setEnabled(false);

    }
    else if (startingPlayer == 2 && difficulty == 4)
    {
        PlayerUsername->setText("Player 2");
        other = true;
        //ThrowBlue_Button->setEnabled(false);
    }

    QString ss;
    if(startingPlayer == 1)
    {
        ss = "-1";
    }
    else if (startingPlayer == 2)
    {
        ss = "-2";
    }
    Game1Scene->SetUser(this->user, ss, this->difficulty, this->isResume); //giving game1scene the user's username to save its history

    if(isResume == true)
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

        QString p, d;
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
        other = false;
        if(query[query.size()-3] == "-11" && difficulty == -7)
        {
            this->other = false;
        }
        else if (query[query.size()-3] == "-12" && difficulty == -7)
        {
            this->other = true;
        }




        for(int i = 0 ; i < query.size()-1 ; i++)
        {
            temp = temp  + query[i] + ",";
        }

        QRegularExpression re(temp);

        if(other == false && this->difficulty == -7)
        {
            temp = temp + "-1,";
        }
        else if (other == true && this->difficulty == -7)
        {
            temp = temp + "-2,";
        }

        if(this->difficulty > -7) //PC always plays his turn after the user plays, thus it is always the users turn when he resumes
        {
            temp = temp + "-1,";
        }

        temp= temp + QString::number(this->difficulty) + "," ;

        dataText.replace(re,temp);

        QFile newData(QDir::currentPath() + "/history.txt");
        data.resize(0);
        if(newData.open(QFile::WriteOnly | QFile::Truncate))
        {
            QTextStream out(&newData);
            out << dataText;
        }
        newData.close();

        if (this->difficulty == -7)
        {
            this->difficulty = 4;
        }
        else if (this->difficulty == -6)
        {
            this->difficulty = 3;
        }
        else if (this->difficulty == -5)
        {
            this->difficulty = 2;
        }
        else if (difficulty == -4)
        {
            this->difficulty = 1;
        }



        int one, two;
        one = query[query.size()-5].toInt()-1;
        two = query[query.size()-4].toInt()-1;

        if(one < 10)
        {
            Game1Scene->player1->MoveP(query[query.size()-5].toInt()-1);
            //Game1Scene->Move(Game1Scene->player1,  query[query.size()-5].toInt()-1);
        }
        else
        {
            Game1Scene->player1->MovePExtra(query[query.size()-5].toInt()-1);
        }

        if(two < 10)
        {
            Game1Scene->player2->MoveP(query[query.size()-4].toInt()-1);
            //Game1Scene->Move(Game1Scene->player2, query[query.size()-4].toInt()-1);
        }
        else
        {
            Game1Scene->player2->MovePExtra(query[query.size()-4].toInt()-1);
        }





    }

}

/**
 * \brief listener function that handles finishing the game, as well as enabling and disabling the throw and end turn buttons according to turns
 * \param Takes no parameter
 * \return nothing (type: void)
 */

void dice :: reveal ()
{
    //here to check for ladders and snakes once done from normal movement
    if (Game1Scene->player1->active == false && Game1Scene->player2->active == false)
    {
        Game1Scene->check(Game1Scene->player1);
        Game1Scene->check(Game1Scene->player2);
        if((Game1Scene->player1->cell == 99 || Game1Scene->player2->cell == 99) && once == false)
        {
            once = true;
            Game1Scene->player1->myturn = false;
            Game1Scene->player2->myturn = false;
            endedturn = false;
            endedturnPC = false;
            this->ThrowBlue_Button->setEnabled(false);
            this->EndTurn_Button->setEnabled(false);
            this->wonturn();


            //this inserts a 'w' or 'l' when the player wins or loses
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
                {break; }
            }
            file.close();

            for(int i = 0 ; i < query.size()-1 ; i++)
            {
                temp = temp  + query[i] + ",";
            }
            QRegularExpression re(temp);
            if(Game1Scene->player1->cell == 99)
            {
                temp = temp + "w,";
            }
            else
            {
                temp = temp + "l,";
            }
            dataText.replace(re, temp);
            QFile newData(QDir::currentPath() + "/history.txt");
            data.resize(0);
            if(newData.open(QFile::WriteOnly | QFile::Truncate)) {
                QTextStream out(&newData);
                out << dataText;           }
            newData.close();

        }

    }

    //if player1 wants to press the end button, it has to be his turn, and both players shouldnt be in the process of moving their icons
    // and he must have pushed the throw button once
    //here for 2 players
    if (Game1Scene->player1->active == false && Game1Scene->player2->active == false && endedturn == true && difficulty == 4)
       {
            this->EndTurn_Button->setEnabled(true);
       }

       if((Game1Scene->player1->active == true || Game1Scene->player2->active == true) && difficulty == 4)
       {
           this->EndTurn_Button->setEnabled(false);
       }


       //here for 2 players changing names
       //Starting username belongs to starting player which has myturn = true
       if(Game1Scene->player1->myturn == true && Game1Scene->player2->myturn == false && difficulty < 4)
       {
           PlayerUsername->setText("Player: " + name);
       }
       else if (Game1Scene->player1->myturn == false && Game1Scene->player2->myturn == true && difficulty < 4)
       {
           PlayerUsername->setText("Player PC");
       }

       //other is a boolean that determines if it is player1 or player2's turn
       if(other == false && difficulty == 4)
       {
           PlayerUsername->setText("Player: " + name);
       }
       else if (other == true && difficulty == 4)
       {
           PlayerUsername->setText("Player 2");
       }


       //here for the PC

       //makes taketurns equal true for the PC to take his turn when both players arent active and it is his turn
    if (Game1Scene->player1->active == false && Game1Scene->player2->active == false && Game1Scene->player2->myturn == true && difficulty < 4)
    {
         taketurns = true;

    }

    if (Game1Scene->player1->active == false && Game1Scene->player2->active == false && endedturn == true && difficulty < 4)
       {
            this->EndTurn_Button->setEnabled(true);
       }

    if((Game1Scene->player1->active == true || Game1Scene->player2->active == true) && difficulty < 4)
    {
        this->EndTurn_Button->setEnabled(false);
    }


    if(Game1Scene->player1->active == false && Game1Scene->player2->active == false && endedturnPC == true && difficulty < 4)
    {
        this->ThrowBlue_Button->setEnabled(true);
    }



}


//keeps listening if taketurn is true or not, taketurns becomes true when none of the players are active and if it is PC's turn
//it becomes PC's turn if he is the starting player or if the other player ends his turn
//depends on Game1Scene->player2->myturn == true

/**
 * \brief listener function that starts a PC's turn
 * \param Takes no parameter
 * \return nothing (type: void)
 */

void dice :: listener()
{
    if(taketurns == true)
    {
        if(difficulty == 1 || difficulty == 2 || difficulty == 3)
        {
            this->ThrowBluePC();
            this->EndTurnPC();
            //cout << "here" << endl;
            taketurns = false;
        }
        else
        {
            //can never reach this else
            //redundant
            //this->ThrowBlue_Button->setEnabled(false);
        }
    }
    else
    {}
}

/**
 * \brief Function ends a game and shows who won
 * \param Takes no parameter
 * \return nothing (type: void)
 */

void dice :: wonturn()
{
    Game1_View->close();
    this->close();

    winlose * endscene ;
    endscene = new winlose();
    if(Game1Scene->player1->cell == 99)
    {
        endscene->setlabel(this->user,1);
    }
    else
    {
        endscene->setlabel(this->user,2);
    }
    endscene->show();
}


/**
 * \brief Function that overrides the "x" button on the dice widget with behaviour similar to ending a game
 * \param QCloseEvent
 * \return nothing (type: void)
 */

 void dice :: closeEvent(QCloseEvent *bar)
 {
     Game1_View->close();
     this->close();
     BackToMain = new MainScreen();
     BackToMain->setUser(this->user);
     BackToMain->show();

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


     //-12 means it is player 2's turn next time he resumes and -11 means player 1



     if(query[1] == "-3")
     {}
     else
     {
         if(other == true && this->difficulty == 4)
         {
             temp = temp + "-12,";
         }
         else if (other == false && this->difficulty == 4)
         {
             temp = temp + "-11,";
         }
         else if (this->difficulty < 4)
         {
             temp = temp + "-11,";
         }



        temp = temp + "x,";
     }
     dataText.replace(re, temp);




     QFile newData(QDir::currentPath() + "/history.txt");
     data.resize(0);
     if(newData.open(QFile::WriteOnly | QFile::Truncate))
     {
         QTextStream out(&newData);
         out << dataText;
     }
     newData.close();
 }

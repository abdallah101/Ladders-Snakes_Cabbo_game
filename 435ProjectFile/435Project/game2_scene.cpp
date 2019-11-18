#include "game2_scene.h"
#include <QImage>
#include <QDir>
#include <time.h>
#include <QGraphicsView>
#include <mainscreen.h>
#include <QMouseEvent>
#include <vector>
#include <QTextStream>
using namespace std;


game2_scene::game2_scene()
{
    //initializing variables
    turn1 = true;
    turn2 = false;
    turn3 = false;
    fate = false;
    nbofFlips = 0;
    AllowedFlips = 1;
    FirstTurn = true;
    piledUp = false;
    this->started = false;
    choosing = false;
    for(int i = 0 ; i < 4 ; i++)
    {player2[i] = -1; player3[i] = -1;picked[i]=false;}


    //setting the GraphicsView with custom class in order to override the exit button
    Game2_View = new ViewGameTwo();
    Game2_View->setFixedHeight(900);
    Game2_View->setFixedWidth(900);
    Game2_View->setScene(this);
    Game2_View->setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    Game2_View->setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));

    push = new QProgressBar();
    this->addWidget(push);
    exitB = new QGraphicsPixmapItem();

    exitB->setPixmap((QPixmap(QDir::currentPath() + "/Images/ExitB.png")).scaled(100,100));
    this->addItem(exitB);
    exitB->setPos(800,800);

    //setting the background
    QImage green;
    this->setSceneRect(0,0,900,900);
    if (green.load(QDir::currentPath() + "/Images/CardBackground.jpg"))
    {
        this->setBackgroundBrush(QBrush(green.scaledToHeight(900).scaledToWidth(900)));
    }



    //1 to 13 is clubs, then spades then hearts then diamonds
    //pile[i] ==1 means the card hasn't been drawn (fromPile)
    //drawn is the same but for the cards that have been drawn and put into the toPile
    for(int i = 0 ; i < 52; i++)
    {
        pile[i] = 1;
        drawn[i] = 0;
    }


    //generating random cards for the players and removing them from the pile
    srand(time(0));
    for(int i = 0 ; i < 12; i ++)
    {

        playerCards.push_back(new Cards());
        while(playerCards[i]->number == -1)
        {
            int x = 1 + rand()%32;
            int y  = 1 + rand()%22;
            x = x + y;

            if(pile[x] == 1)
            {
                playerCards[i]->number = x;
                pile[x] = 0;
            }

        }
    }


    //making the cards selectable (at the moment this became redundant because of the usage of mousepressevent)
    for(int i = 0 ; i < 12; i++)
    {
        playerCards[i]->setFlag(QGraphicsItem::ItemIsSelectable);
    }

    fromPile = new Cards();
    fromPile->setFlag(QGraphicsItem::ItemIsSelectable);
    toPile = new Cards();
    toPile->setFlag(QGraphicsItem::ItemIsSelectable);

    //set up here the initial position of the cards
    //player1
    playerCards[0]->setPixmap((QPixmap(QDir::currentPath() + "/Images/CardBack.png")).scaled(125,125));
    this->addItem(playerCards[0]);
    playerCards[0]->setPos(325,600);
    playerCards[0]->x = 325;
    playerCards[0]->y = 600;

    playerCards[1]->setPixmap((QPixmap(QDir::currentPath() + "/Images/CardBack.png")).scaled(125,125));
    this->addItem(playerCards[1]);
    playerCards[1]->setPos(450,600);
    playerCards[1]->x = 450;
    playerCards[1]->y = 600;

    playerCards[2]->setPixmap((QPixmap(QDir::currentPath() + "/Images/CardBack.png")).scaled(125,125));
    this->addItem(playerCards[2]);
    playerCards[2]->setPos(325,725);
    playerCards[2]->x = 325;
    playerCards[2]->y = 725;

    playerCards[3]->setPixmap((QPixmap(QDir::currentPath() + "/Images/CardBack.png")).scaled(125,125));
    this->addItem(playerCards[3]);
    playerCards[3]->setPos(450,725);
    playerCards[3]->x = 450;
    playerCards[3]->y = 725;

    //player2
    playerCards[4]->setPixmap((QPixmap(QDir::currentPath() + "/Images/CardBack.png")).scaled(125,125));
    this->addItem(playerCards[4]);
    playerCards[4]->setPos(150,0);
    playerCards[4]->x = 150;


    playerCards[5]->setPixmap((QPixmap(QDir::currentPath() + "/Images/CardBack.png")).scaled(125,125));
    this->addItem(playerCards[5]);
    playerCards[5]->setPos(275,0);
    playerCards[5]->x = 275;


    playerCards[6]->setPixmap((QPixmap(QDir::currentPath() + "/Images/CardBack.png")).scaled(125,125));
    this->addItem(playerCards[6]);
    playerCards[6]->setPos(150,125);
    playerCards[6]->x = 150;
    playerCards[6]->y = 125;

    playerCards[7]->setPixmap((QPixmap(QDir::currentPath() + "/Images/CardBack.png")).scaled(125,125));
    this->addItem(playerCards[7]);
    playerCards[7]->setPos(275,125);
    playerCards[7]->x = 275;
    playerCards[7]->y = 125;


    //player3
    playerCards[8]->setPixmap((QPixmap(QDir::currentPath() + "/Images/CardBack.png")).scaled(125,125));
    this->addItem(playerCards[8]);
    playerCards[8]->setPos(500,0);
    playerCards[8]->x = 500;


    playerCards[9]->setPixmap((QPixmap(QDir::currentPath() + "/Images/CardBack.png")).scaled(125,125));
    this->addItem(playerCards[9]);
    playerCards[9]->setPos(625,0);
    playerCards[9]->x = 625;


    playerCards[10]->setPixmap((QPixmap(QDir::currentPath() + "/Images/CardBack.png")).scaled(125,125));
    this->addItem(playerCards[10]);
    playerCards[10]->setPos(500,125);
    playerCards[10]->x = 500;
    playerCards[10]->y = 125;

    playerCards[11]->setPixmap((QPixmap(QDir::currentPath() + "/Images/CardBack.png")).scaled(125,125));
    this->addItem(playerCards[11]);
    playerCards[11]->setPos(625,125);
    playerCards[11]->x = 625;
    playerCards[11]->y = 125;

    //from pile
    fromPile->setPixmap((QPixmap(QDir::currentPath() + "/Images/CardBack.png")).scaled(125,125));
    this->addItem(fromPile);
    fromPile->setPos(387.5,387.5);


    //from pile
    toPile->setPixmap((QPixmap(QDir::currentPath() + "/Images/CardBack.png")).scaled(125,125));
    this->addItem(toPile);
    toPile->setPos(600,387.5);

    int x = rand()%4;
    int y = rand()%4;
    while(x == y)
    {
        x = rand()%4;
    }

    player2[x] = playerCards[x+4]->number;
    player2[y] = playerCards[y+4]->number;

    x = rand()%4;
    y = rand()%4;
    while(x==y)
    {
        x = rand()%4;
    }

    player3[x] = playerCards[x+8]->number;
    player3[y] = playerCards[y+8]->number;

    /*for(int i = 4 ; i < 12; i++)
    {
        if(player2[i-4] != -1)
        {
        playerCards[i]->setPixmap((QPixmap(QDir::currentPath() + "/Images/"+ QString::number(playerCards[i]->number) +".png")).scaled(80,100));
        }
        else if (player3[i-8] != -1)
        {
         playerCards[i]->setPixmap((QPixmap(QDir::currentPath() + "/Images/"+ QString::number(playerCards[i]->number) +".png")).scaled(80,100));
        }

    }*/


    /**
     * flips cards back after a duration
     */
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(change()));


    /**
     * changes variables to keep game going
     */
    timer1 = new QTimer();
    timer1->start(100);
    connect(timer1, SIGNAL(timeout()), this, SLOT(update()));


}



void game2_scene :: setUser(QString a)
{
    this->user = a;
    this->Game2_View->setUser(a);
    this->started = true;
}

void game2_scene :: change()
{

    for(int i = 0 ; i < 12 ; i++)
    {
        playerCards[i]->setPixmap((QPixmap(QDir::currentPath() + "/Images/CardBack.png")).scaled(125,125));
    }

    //timer->stop();

}

void game2_scene :: mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPoint origin = Game2_View->mapFromGlobal(QCursor::pos());
    QPointF relativeOrigin = Game2_View->mapToScene(origin);
    if(this->itemAt(relativeOrigin,QTransform()) != NULL)
    {
        //Do what you want here
        //for debugging

                //first turn, user here sees 2 of his cards, players 2 & 3 already saw their 2 cards
                if(FirstTurn == true && nbofFlips < 2 && this->itemAt(relativeOrigin,QTransform())->y() > 510.5)
                {
                    QTextStream out(stdout);
                    out << this->itemAt(relativeOrigin,QTransform())->x() << " : " << this->itemAt(relativeOrigin,QTransform())->y() << endl;
                     //let user see 2 cards, need timerot showcase his 2 cards for a while, keep 1st card open till he chooses another card then
                     //start the timer

                     //QTextStream out(stdout);
                     //out << this->itemAt(relativeOrigin,QTransform())->x() << " : " << this->itemAt(relativeOrigin,QTransform())->y() << endl;

                    for(int i = 0 ; i < 4; i++)
                    {
                        if(this->itemAt(relativeOrigin,QTransform())->x() == playerCards[i]->x && this->itemAt(relativeOrigin,QTransform())->y() == playerCards[i]->y && picked[i] == false)
                        {
                            playerCards[i]->setPixmap((QPixmap(QDir::currentPath() + "/Images/"+ QString::number(playerCards[i]->number) +".png")).scaled(80,100));

                            nbofFlips += 1;
                            picked[i] = true;
                            break;
                        }
                    }


                }


                if(this->itemAt(relativeOrigin,QTransform()) != NULL)
                {
                //here user gets to see what is at the top of the deck (fromPile)
                if (FirstTurn == false && this->itemAt(relativeOrigin,QTransform())->y() == 387.5 && turn1 == true && choosing == false
                        && this->itemAt(relativeOrigin,QTransform())->x() == 387.5)
                {
                    QTextStream out(stdout);
                    out << this->itemAt(relativeOrigin,QTransform())->x() << " : " << this->itemAt(relativeOrigin,QTransform())->y() << endl;

                    int x = rand()%52;
                    while(pile[x] == 0)
                    {
                        x = rand()%52;
                    }

                    pile[x] = 0;
                    fromPile->number = x + 1;
                    fromPile->setPixmap((QPixmap(QDir::currentPath() + "/Images/"+ QString::number(x) +".png")).scaled(80,100));
                    choosing = true;

                }
                }

                //here the user either replaces one of his cards or places the card into the discard pile (toPile) or gets a choice card
                if(this->itemAt(relativeOrigin,QTransform()) != NULL)

                {
                if(FirstTurn == false && choosing == true && turn1 == true && this->itemAt(relativeOrigin,QTransform())->y() == 387.5 && this->itemAt(relativeOrigin,QTransform())->x() == 600)
                {
                    QTextStream out(stdout);
                    out << this->itemAt(relativeOrigin,QTransform())->x() << " : " << this->itemAt(relativeOrigin,QTransform())->y() << endl;
                    toPile->number = fromPile->number;
                    fromPile->setPixmap((QPixmap(QDir::currentPath() + "/Images/CardBack.png")).scaled(125,125));
                    toPile->setPixmap((QPixmap(QDir::currentPath() + "/Images/" + QString::number(toPile->number) + ".png")).scaled(80,100));
                    choosing = false;
                    turn1 = false;
                    turn2 = true;
                    piledUp = true;
                }
                else if (FirstTurn == false && choosing == true && turn1 == true && this->itemAt(relativeOrigin,QTransform())->y() > 510.5 && (fromPile->number < 7 || (fromPile->number >= 14 && fromPile->number < 20) || (fromPile->number >= 27 && fromPile->number <= 32) || (fromPile->number >= 40 && fromPile->number <= 45)))
                {
                    QTextStream out(stdout);
                    out << this->itemAt(relativeOrigin,QTransform())->x() << " : " << this->itemAt(relativeOrigin,QTransform())->y() << endl;

                    for(int i = 0 ; i < 4 ; i++)
                    {
                        if(this->itemAt(relativeOrigin,QTransform())->x() == playerCards[i]->x && this->itemAt(relativeOrigin,QTransform())->y() == playerCards[i]->y)
                        {
                            playerCards[i]->number = fromPile->number;
                            fromPile->setPixmap((QPixmap(QDir::currentPath() + "/Images/CardBack.png")).scaled(125,125));
                            choosing = false;
                            turn1 = false;
                            turn2 = true;
                            break;
                        }
                    }


                }
                //put here action for choice cards
                else if(FirstTurn == false && choosing == true && turn1 == true && this->itemAt(relativeOrigin,QTransform())->y() > 510.5 && (fromPile->number == 7 || fromPile->number == 8 || fromPile->number == 20 || fromPile->number == 21 || fromPile->number == 33 || fromPile->number == 34 || fromPile->number == 46 || fromPile->number == 47)
                        )
                {
                    for(int i = 0 ; i < 4 ; i++)
                    {
                        if(this->itemAt(relativeOrigin,QTransform())->x() == playerCards[i]->x && this->itemAt(relativeOrigin,QTransform())->y() == playerCards[i]->y)
                        {
                            fromPile->setPixmap((QPixmap(QDir::currentPath() + "/Images/CardBack.png")).scaled(125,125));
                            playerCards[i]->setPixmap((QPixmap(QDir::currentPath() + "/Images/"+ QString::number(playerCards[i]->number) +".png")).scaled(80,100));
                            fate = true;
                            choosing = false;
                            turn1 = false;
                            turn2 = true;
                            toPile->number = fromPile->number;
                            break;
                        }
                    }

                }
                else if (FirstTurn == false && choosing == true && turn1 == true && this->itemAt(relativeOrigin,QTransform())->y() < 370 && (fromPile->number == 9 || fromPile->number == 10 || fromPile->number == 22 || fromPile->number == 23 || fromPile->number == 35 || fromPile->number == 36 || fromPile->number == 48 || fromPile->number == 49))
                {


                    for(int i = 4 ; i < 12; i++)
                    {
                        if(this->itemAt(relativeOrigin,QTransform())->x() == playerCards[i]->x && this->itemAt(relativeOrigin,QTransform())->y() == playerCards[i]->y)
                        {
                            fromPile->setPixmap((QPixmap(QDir::currentPath() + "/Images/CardBack.png")).scaled(125,125));
                            playerCards[i]->setPixmap((QPixmap(QDir::currentPath() + "/Images/"+ QString::number(playerCards[i]->number) +".png")).scaled(80,100));
                            fate = true;
                            break;

                        }
                    }

                }
                else if (FirstTurn == false && choosing == true && turn1 == true && this->itemAt(relativeOrigin,QTransform())->y() < 370 && (fromPile->number == 11 || fromPile->number == 12 || fromPile->number == 24 || fromPile->number == 25 || fromPile->number == 37 || fromPile->number == 38 || fromPile->number == 50 || fromPile->number == 51))
                {

                }
                }

                if(this->itemAt(relativeOrigin,QTransform()) != NULL)
                {
                if(this->itemAt(relativeOrigin,QTransform())->x() == 800 && this->itemAt(relativeOrigin,QTransform())->y() == 800)
                {
                    this->Game2_View->close();
                    MainScreen * BacktoMain = new MainScreen();
                    BacktoMain->setUser(this->user);
                    BacktoMain->show();
                    this->clear();
                    delete this;


                }
                }


    }


}

void game2_scene :: update()
{

    if(nbofFlips == 2)
    {
        //+1 to nbofFLips since we dont use it again and it stays at 2 which will keep this looping
        nbofFlips += 1;
        FirstTurn = false;
        timer->start(4000);
    }

    if(fate == true)
    {
        timer->start(4000);
        fate = false;
    }
}


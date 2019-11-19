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
    swap[0] = -1;
    swap[1] = -1;
    replacingD = false;
    for(int i = 0 ; i < 8 ; i++)
    {player2memory[i] = -1; player3memory[i] = -1;}


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


    //set up here the initial position of the cards (initial position by defualt is 0)
    //player1
    playerCards[0]->x = 325;
    playerCards[0]->y = 600;
    playerCards[1]->x = 450;
    playerCards[1]->y = 600;
    playerCards[2]->x = 325;
    playerCards[2]->y = 725;
    playerCards[3]->x = 450;
    playerCards[3]->y = 725;

    //player2
    playerCards[4]->x = 150;
    playerCards[5]->x = 275;
    playerCards[6]->x = 150;
    playerCards[6]->y = 125;
    playerCards[7]->x = 275;
    playerCards[7]->y = 125;


    //player3
    playerCards[8]->x = 500;
    playerCards[9]->x = 625;
    playerCards[10]->x = 500;
    playerCards[10]->y = 125;
    playerCards[11]->x = 625;
    playerCards[11]->y = 125;

    for(int i = 0 ; i < 12 ; i++)
    {
        playerCards[i]->setPixmap((QPixmap(QDir::currentPath() + "/Images/CardBack.png")).scaled(125,125));
        this->addItem(playerCards[i]);
        playerCards[i]->setPos(playerCards[i]->x,playerCards[i]->y);
    }

    //from pile
    fromPile->setPixmap((QPixmap(QDir::currentPath() + "/Images/CardBack.png")).scaled(125,125));
    this->addItem(fromPile);
    fromPile->setPos(387.5,387.5);


    //from pile
    toPile->setPixmap((QPixmap(QDir::currentPath() + "/Images/CardBack.png")).scaled(125,125));
    this->addItem(toPile);
    toPile->setPos(600,387.5);

    //letting players 2 & 3 know 2 of their cards just like the player at the beginning of the turn
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

    /**
     * keeps checking if it's player 2's turn
     */
    player2timer = new QTimer();
    player2timer->start(100);
    connect(player2timer, SIGNAL(timeout()), this, SLOT(player2turn()));

    /**
     * keeps checking if it's player 3's turn
     */
    player3timer = new QTimer();
    player3timer->start(100);
    connect(player3timer, SIGNAL(timeout()), this, SLOT(player3turn()));


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

    //When the player doesn't have any moves left, player2's turn begins by making turn2  = true and for player3 its turn3 = true
    //player2 is responsible for making turn3 = true

    if(this->itemAt(relativeOrigin,QTransform()) != NULL)
    {
        //Here the mouse returned an object of type QGraphicsItem, use its (x,y) position to do what you want
        //since we have several if statements, keep on checking for NULL at each if, since changing/removing the item will lose you the (x,y) you have
        //causing a segmentation fault when trying to get the (x,y) at the next if statement

                //first turn, user here sees 2 of his cards, players 2 & 3 already saw their 2 cards
                if(FirstTurn == true && nbofFlips < 2 && this->itemAt(relativeOrigin,QTransform())->y() > 510.5)
                {
                    QTextStream out(stdout);
                    out << this->itemAt(relativeOrigin,QTransform())->x() << " : " << this->itemAt(relativeOrigin,QTransform())->y() << endl;
                     //let user see 2 cards, need timer to showcase his 2 cards for a while, keep 1st card open till he chooses another card then
                     //start the timer

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
                    //x = 10;
                    //if you want to try a choice card then set the top of the deck to be the card you want (for debugging)
                    pile[x] = 0;
                    fromPile->number = x + 1;
                    fromPile->setPixmap((QPixmap(QDir::currentPath() + "/Images/"+ QString::number(x + 1) +".png")).scaled(80,100));
                    choosing = true;

                }
                }

                //here the user either replaces one of his cards or places the card into the discard pile (toPile) or gets a choice card
                if(this->itemAt(relativeOrigin,QTransform()) != NULL)

                {
                //puts card into discard pile
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
                //replaces card with one of his
                else if (FirstTurn == false && choosing == true && turn1 == true && this->itemAt(relativeOrigin,QTransform())->y() > 510.5 && (fromPile->number < 7 || (fromPile->number >= 14 && fromPile->number < 20) || (fromPile->number >= 27 && fromPile->number <= 32) || (fromPile->number >= 40 && fromPile->number <= 45)))
                {
                    QTextStream out(stdout);

                    for(int i = 0 ; i < 4 ; i++)
                    {
                        if(this->itemAt(relativeOrigin,QTransform())->x() == playerCards[i]->x && this->itemAt(relativeOrigin,QTransform())->y() == playerCards[i]->y)
                        {
                            toPile->number = playerCards[i]->number;
                            toPile->setPixmap((QPixmap(QDir::currentPath() + "/Images/" + QString::number(toPile->number) + ".png")).scaled(80,100));
                            playerCards[i]->number = fromPile->number;

                            out << "from: " << fromPile->number << " , " << "playerCards[" << i << "]: " << playerCards[i]->number << endl;

                            fromPile->setPixmap((QPixmap(QDir::currentPath() + "/Images/CardBack.png")).scaled(125,125));
                            choosing = false;
                            turn1 = false;
                            turn2 = true;
                            piledUp = true;

                            break;
                        }
                    }


                }
                //put here action for CHOICE CARDS
                //***********************************
                //sees 1 of his cards
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
                //sees 1 card from other players
                else if (FirstTurn == false && choosing == true && turn1 == true && this->itemAt(relativeOrigin,QTransform())->y() < 370 && (fromPile->number == 9 || fromPile->number == 10 || fromPile->number == 22 || fromPile->number == 23 || fromPile->number == 35 || fromPile->number == 36 || fromPile->number == 48 || fromPile->number == 49))
                {


                    for(int i = 4 ; i < 12; i++)
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
                //swaps 2 cards
                else if (FirstTurn == false && choosing == true && turn1 == true &&  (fromPile->number == 11 || fromPile->number == 12 || fromPile->number == 24 || fromPile->number == 25 || fromPile->number == 37 || fromPile->number == 38 || fromPile->number == 50 || fromPile->number == 51))
                {
                    if(this->itemAt(relativeOrigin,QTransform()) != NULL)
                    {
                    if(swap[0] == -1) //still didn't choose first card
                    {
                        for(int i = 0 ; i < 12; i++)
                        {
                            if(this->itemAt(relativeOrigin,QTransform())->x() == playerCards[i]->x && this->itemAt(relativeOrigin,QTransform())->y() == playerCards[i]->y)
                            {
                                if(i < 4)
                                {
                                    playerCards[i]->setPixmap((QPixmap(QDir::currentPath() + "/Images/"+ QString::number(playerCards[i]->number) +".png")).scaled(80,100));
                                    swap[0] = i;

                                }
                                else
                                {
                                    playerCards[i]->setPixmap((QPixmap(QDir::currentPath() + "/Images/"+ QString::number(playerCards[i]->number) +".png")).scaled(80,100));
                                    swap[0] = i + 100;

                                }
                                break;

                            }
                        }
                    }
                    else if (swap[1] == -1 && swap[0] != -1) //still didnt choose second card
                    {
                        if(swap[0] > 100) //meaning he chose from the other players first
                        {
                            for(int i = 0 ; i < 4; i++)
                            {
                                if(this->itemAt(relativeOrigin,QTransform())->x() == playerCards[i]->x && this->itemAt(relativeOrigin,QTransform())->y() == playerCards[i]->y)
                                {
                                    playerCards[i]->setPixmap((QPixmap(QDir::currentPath() + "/Images/"+ QString::number(playerCards[i]->number) +".png")).scaled(80,100));
                                    fromPile->setPixmap((QPixmap(QDir::currentPath() + "/Images/CardBack.png")).scaled(125,125));
                                    fate = true;
                                    swap[1] = i;
                                    swap[0] = swap[0] - 100;
                                    //QTextStream out(stdout);
                                    //out << "Before: " << playerCards[swap[0]]->number << " : " << playerCards[swap[1]]->number << endl;
                                    this->swapCards(swap[0],swap[1]);
                                    //out << "After: " << playerCards[swap[0]]->number << " : " << playerCards[swap[1]]->number << endl;
                                    swap[0] = -1;
                                    swap[1] = -1;
                                    choosing = false;
                                    turn1 = false;
                                    turn2 = true;
                                    toPile->number = fromPile->number;
                                    break;

                                }
                            }
                        }
                        else //he chose 1 of his cards first
                        {
                            for(int i = 4; i < 12; i++)
                            {
                                if(this->itemAt(relativeOrigin,QTransform())->x() == playerCards[i]->x && this->itemAt(relativeOrigin,QTransform())->y() == playerCards[i]->y)
                                {
                                    playerCards[i]->setPixmap((QPixmap(QDir::currentPath() + "/Images/"+ QString::number(playerCards[i]->number) +".png")).scaled(80,100));
                                    fromPile->setPixmap((QPixmap(QDir::currentPath() + "/Images/CardBack.png")).scaled(125,125));
                                    swap[1] = i;
                                    fate = true;

                                    QTextStream out(stdout);
                                    out << "Before: " << playerCards[swap[0]]->number << " : " << playerCards[swap[1]]->number << endl;
                                    this->swapCards(swap[0],swap[1]);

                                    out << "After: " << playerCards[swap[0]]->number << " : " << playerCards[swap[1]]->number << endl;

                                    swap[0] = -1;
                                    swap[1] = -1;
                                    choosing = false;
                                    turn1 = false;
                                    turn2 = true;
                                    toPile->number = fromPile->number;
                                    break;

                                }
                            }
                        }

                    }
                    }
                }
                }


                //here player is taking the card from the discard pile and replacing it by one of his own cards
                if(this->itemAt(relativeOrigin,QTransform()) != NULL)
                {

                    if(piledUp == true && FirstTurn == false && choosing == false && turn1 == true && this->itemAt(relativeOrigin,QTransform())->y() == 387.5 && this->itemAt(relativeOrigin,QTransform())->x() == 600)
                    {
                        replacingD = true;
                    }
                    else if(piledUp == true && FirstTurn == false && choosing == false && turn1 == true && this->itemAt(relativeOrigin,QTransform())->y() > 510.5 && replacingD == true)
                    {
                        for(int i = 0 ; i < 4 ; i++)
                        {
                            if(this->itemAt(relativeOrigin, QTransform())->x() == playerCards[i]->x && this->itemAt(relativeOrigin, QTransform())->y() == playerCards[i]->y)
                            {
                                int l = toPile->number;
                                toPile->number = playerCards[i]->number;
                                playerCards[i]->number = l;
                                replacingD = false;
                                turn1 = false;
                                turn2 = true;
                                break;
                            }
                        }
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

void game2_scene :: swapCards(int first, int second)
{
    int x = playerCards[first]->number;
    playerCards[first]->number = playerCards[second]->number;
    playerCards[second]->number = x;
}

void game2_scene :: player2turn()
{
    if(turn2 == true)
    {
        push->setValue(25);
        //1. player either looks at discard pile (toPile) and checks what he already knows about his cards to replace one of his or goes to step 2
        //2. check the top of the pile (fromPile),
        //   a. if its a number less than a card he knows from his cards, then replace else put in discard pile (toPile)
        //   b. if it's a peek card then look at one of his cards that he doesn't know about (if he knows them all then discard it)
        //   c. if its a spy card, randomly pick a card from the other players that he doesn't know about (if he knows them all the discard it)
        //   d. if it's a swap card, then check his knowledge about the other player's card, if he finds a card that is less than one of the cards he knows
        //      about from his card, then swap, if there isn't or he doesn't know any cards from the other players then swap randomly any card he does not know about

        int value, playervalue, playervalue2;
        bool foundless = false, foundlessfrom = false, foundswap = false;
        if(piledUp == true)
        {//take from pile if less than what he knows he has
            if(toPile->number <= 13)
            {
                value = toPile->number;
            }
            else if (toPile->number >= 14 && toPile->number <= 26 )
            {
                value = toPile->number - 13;
            }
            else if (toPile->number >= 27 && toPile->number <= 39)
            {
                value = toPile->number - 26;
            }
            else
            {
                value = toPile->number - 39;
            }

            for(int i = 4; i < 8; i++)
            {
                if(player2[i-4] <= 13)
                {
                    playervalue = player2[i-4];
                }
                else if (player2[i-4] >= 14 && player2[i-4] <= 26 )
                {
                    playervalue = player2[i-4] - 13;
                }
                else if (player2[i-4] >= 27 && player2[i-4] <= 39)
                {
                    playervalue = player2[i-4] - 26;
                }
                else
                {
                    playervalue = player2[i-4] - 39;
                }
                if(value < playervalue)
                {
                    int j = toPile->number;
                    toPile->number = playerCards[i]->number;
                    playerCards[i]->number = j;
                    player2[i] = j;
                    toPile->setPixmap((QPixmap(QDir::currentPath() + "/Images/" + QString::number(toPile->number) + ".png")).scaled(80,100));
                    foundless = true;
                    turn2 = false;
                    turn3 = true;
                    break;
                }
            }

        }

        if(piledUp == false || foundless == false)
        {
            int x = rand()%52;
            while(pile[x] == 0)
            {
                x = rand()%52;
            }
            pile[x] = 0;
            fromPile->number = x + 1;

            if(fromPile->number <= 13)
            {
                value = fromPile->number;
            }
            else if (fromPile->number >= 14 && fromPile->number <= 26 )
            {
                value = fromPile->number - 13;
            }
            else if (fromPile->number >= 27 && fromPile->number <= 39)
            {
                value = fromPile->number - 26;
            }
            else
            {
                value = fromPile->number - 39;
            }

            //decide if to take card or not
            if(value < 7)
            {

                for(int i = 4; i < 8; i++)
                {
                    if(player2[i-4] <= 13)
                    {
                        playervalue = player2[i-4];
                    }
                    else if (player2[i-4] >= 14 && player2[i-4] <= 26 )
                    {
                        playervalue = player2[i-4] - 13;
                    }
                    else if (player2[i-4] >= 27 && player2[i-4] <= 39)
                    {
                        playervalue = player2[i-4] - 26;
                    }
                    else
                    {
                        playervalue = player2[i-4] - 39;
                    }
                    if(value < playervalue)
                    {
                        int j = fromPile->number;
                        fromPile->number = playerCards[i]->number;
                        playerCards[i]->number = j;
                        player2[i] = j;
                        foundlessfrom = true;
                        turn2 = false;
                        turn3 = true;
                        break;
                    }
                }

                if(foundlessfrom == false)
                {
                    toPile->number = fromPile->number;
                    toPile->setPixmap((QPixmap(QDir::currentPath() + "/Images/" + QString::number(toPile->number) + ".png")).scaled(80,100));
                }

            }
            //see own card
            else if (value > 6 && value < 9)
            {
                for(int i = 4; i < 8 ; i++)
                {
                    if(player2[i] == -1)
                    {
                        player2[i] = playerCards[i]->number;
                        turn2 = false;
                        turn3 = true;
                        break;
                    }
                }
            }
            //player2memory[8]
            //see opponent's card
            else if(value > 8 && value < 11)
            {
                for(int i = 0 ; i < 12; i++)
                {
                    if(i == 4 || i == 5 || i == 6 || i == 7)
                    {}
                    else
                    {
                        if(i < 4 && player2memory[i] == -1)
                        {
                            player2memory[i] = playerCards[i]->number;
                            break;
                        }
                        else if(i > 8 && player2memory[i-4] == -1)
                        {
                            player2memory[i-4] = playerCards[i]->number;
                            break;
                        }
                    }
                }


                toPile->number = fromPile->number;
                toPile->setPixmap((QPixmap(QDir::currentPath() + "/Images/" + QString::number(toPile->number) + ".png")).scaled(80,100));
                turn2 = false;
                turn3 = true;

            }
            else if (value > 10 && value < 13)
            {
                //check for every known card of player2 with every known card form other players, known by player 2, compare and swap if less
                for(int i = 4 ; i < 8 ; i++)
                {
                    if(player2[i-4] != -1)
                    {
                        if(player2[i-4] <= 13)
                        {
                            playervalue = player2[i-4];
                        }
                        else if (player2[i-4] >= 14 && player2[i-4] <= 26 )
                        {
                            playervalue = player2[i-4] - 13;
                        }
                        else if (player2[i-4] >= 27 && player2[i-4] <= 39)
                        {
                            playervalue = player2[i-4] - 26;
                        }
                        else
                        {
                            playervalue = player2[i-4] - 39;
                        }
                        for(int j = 0 ; j < 8 ; j++)
                        {
                            if(player2memory[j] != -1)
                            {
                                if(player2memory[j] <= 13)
                                {
                                    playervalue2 = player2memory[j];
                                }
                                else if (player2memory[j] >= 14 && player2memory[j] <= 26 )
                                {
                                    playervalue2 = player2memory[j] - 13;
                                }
                                else if (player2memory[j] >= 27 && player2memory[j] <= 39)
                                {
                                    playervalue2 = player2memory[j] - 26;
                                }
                                else
                                {
                                    playervalue2 = player2memory[j] - 39;
                                }

                                if(playervalue > playervalue2)
                                {
                                    if(i < 4)
                                    {
                                        //bascially swap the numbers of the 2 found cards, then store in player2's memory the other players new card, and store in player2 his own new card
                                        int l = playerCards[j]->number;
                                        playerCards[i]->number = playerCards[j]->number;
                                        playerCards[j]->number = l;
                                        player2memory[j] = playerCards[j]->number;
                                        player2[i-4] = playerCards[i]->number;
                                        foundswap = true;
                                        break;
                                    }
                                    else if(i > 8)
                                    {
                                        //similarly here but taking into consideration the format of player2's memory
                                        int l = playerCards[j+4]->number;
                                        playerCards[i]->number = playerCards[j+4]->number;
                                        playerCards[j+4]->number = l;
                                        player2memory[j] = playerCards[j+4]->number;
                                        player2[i-4] = playerCards[i]->number;
                                        foundswap = true;
                                        break;
                                    }

                                }

                            }

                    }


                    }

                    if(foundswap == true)
                    {
                        break;
                    }
                }
            }

        }



    }
}

void game2_scene :: player3turn()
{
    if(turn3 == true)
    {
        push->setValue(25);

    }
}

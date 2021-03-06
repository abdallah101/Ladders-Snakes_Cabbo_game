#include "game2_scene.h"
#include <QImage>
#include <QDir>
#include <time.h>
#include <QGraphicsView>
#include <mainscreen.h>
#include <QMouseEvent>
#include <vector>
#include <QTextStream>
#include <iostream>
using namespace std;


game2_scene::game2_scene()
{
    /**
     * initializing variables
     */

    initial();
    FirstTurn = true;
    turn = 1;
    fate = started = false;
    winner = -1;
    cabo = false;
    nbofFlips = 0;
    swap[0] = swap[1] = -1;
    text = new QGraphicsTextItem();
    QFont serifFont("Times", 20, QFont::Bold);
    text->setFont(serifFont);
    text->setDefaultTextColor("#D4AF37");
    text->setPos(300, 300);
    this->addItem(text);
    deleted = false;
    special = false;
    cabo = false;

    /**
      * Create players
      */

    for(int i = 0; i <3; i++)
    {
        p[i] = new g2_player();
    }


    /**
      * Initialize the players card, memory1 and memory2 arrays entries to - 1 : everything is unknown in the beginning
      * For every player set the other players as opponents
      */

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            p[i]->card[j] = p[i]->memory1[j] = p[i]->memory2[j] = -1;
        }
    }


    /**
      * Generate an ordered deck of cards
      */

    pair <int, int> a[52];
    for (int i = 0; i < 52; i++)
    {
        a[i].first = i%13;
        a[i].second = i/13;
    }



    /**
      * Shuffle randomly
      */

    srand(time(0));
    for (int i = 0; i < 100; i++)
    {
        int x = rand() % 52, y = rand() % 52;
        pair <int, int> temp  = a[x];
        a[x] = a[y];
        a[y] = temp;
    }



    /**
      * Fill the stack and distribute the 12 remanining cards to the 3 players (4 cards each).
      */

    for (int i = 0; i < 40; i++)
    {
        pile.push(a[i]);
    }

    int j = 0, k = 0;
    for (int i = 40; i < 52; i++)
    {
        c[i%3][j] = a[i];
        if (k == 3) j++;
        k = (k+1)%4;
    }



    /**
     * Setting the GraphicsView with custom class in order to override the exit button
     */

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


    CallCabbo = new QGraphicsPixmapItem();
    CallCabbo->setPixmap((QPixmap(QDir::currentPath() + "/Images/EndButton.png")).scaled(100,100));
    this->addItem(CallCabbo);
    CallCabbo->setPos(0,400);



    /**
     * Setting the background
     */

    QImage green;
    this->setSceneRect(0,0,900,900);
    if (green.load(QDir::currentPath() + "/Images/CardBackground.jpg"))
    {
        this->setBackgroundBrush(QBrush(green.scaledToHeight(900).scaledToWidth(900)));
    }



    /**
     * making the cards selectable (at the moment this became redundant because of the usage of mousepressevent)
     */


    for(int i = 0 ; i < 12; i ++)
    {
        playerCards.push_back(new Cards());
        playerCards[i]->number = c[i/4][i%4].first + c[i/4][i%4].second * 13 + 1;
    }

    for(int i = 0 ; i < 12; i++)
    {
        playerCards[i]->setFlag(QGraphicsItem::ItemIsSelectable);
    }



    /**
      * frompile is the card on top of the stack pile
      */

    fromPile = new Cards();
    fromPile->setFlag(QGraphicsItem::ItemIsSelectable);



    /**
      * topile is the card on top of the stack pile
      */

    toPile = new Cards();
    toPile->setFlag(QGraphicsItem::ItemIsSelectable);



    /**
     * set up here the initial position of the cards (initial position by defualt is 0)
     */

    /**
     * player1
     */


    playerCards[0]->x = 325;
    playerCards[0]->y = 600;
    playerCards[1]->x = 450;
    playerCards[1]->y = 600;
    playerCards[2]->x = 325;
    playerCards[2]->y = 725;
    playerCards[3]->x = 450;
    playerCards[3]->y = 725;



    /**
      * player2
      */

    playerCards[4]->x = 150;
    playerCards[5]->x = 275;
    playerCards[6]->x = 150;
    playerCards[6]->y = 125;
    playerCards[7]->x = 275;
    playerCards[7]->y = 125;



    /**
     * player3
     */

    playerCards[8]->x = 500;
    playerCards[9]->x = 625;
    playerCards[10]->x = 500;
    playerCards[10]->y = 125;
    playerCards[11]->x = 625;
    playerCards[11]->y = 125;



    /**
      * The cards are initially flipped
      */

    for(int i = 0 ; i < 12 ; i++)
    {
        playerCards[i]->setPixmap((QPixmap(QDir::currentPath() + "/Images/CardBack.png")).scaled(125,125));
        this->addItem(playerCards[i]);
        playerCards[i]->setPos(playerCards[i]->x,playerCards[i]->y);
    }



    /**
     * from pile
     */

    fromPile->setPixmap((QPixmap(QDir::currentPath() + "/Images/CardBack.png")).scaled(125,125));
    this->addItem(fromPile);
    fromPile->setPos(387.5,387.5);



    /**
     * to pile
     */

    toPile->setPixmap((QPixmap(QDir::currentPath() + "/Images/empty.png")).scaled(125,125));
    this->addItem(toPile);
    toPile->setPos(600,387.5);



    /**
     * @brief Call startingTurn for every player to check 2 of his cards
     */

    startingTurn();



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
     * changes variables to keep game going
     */

    timer2 = new QTimer();
    timer2->start(100);
    //connect(timer2, SIGNAL(timeout()), this, SLOT(g2_end()));

    //cout << turn << "***\n";
}


void game2_scene :: setUser(QString a)
{
    this->user = a;
    this->Game2_View->setUser(a);
    this->started = true;
}



/**
 * @brief game2_scene::change flipp all cards backwards.
 */

void game2_scene :: change()
{

    if (cabo || pile.empty()) return;

    for(int i = 0 ; i < 12 ; i++)
    {
        playerCards[i]->setPixmap((QPixmap(QDir::currentPath() + "/Images/CardBack.png")).scaled(125,125));
    }


    //timer->stop();
}



void game2_scene :: mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (turn != 1 || pile.empty() || cabo) return;
    QPoint origin = Game2_View->mapFromGlobal(QCursor::pos());
    QPointF relativeOrigin = Game2_View->mapToScene(origin);

    /**
     * When the player doesn't have any moves left, player2's turn begins by making turn = 2 and for player3 its turn = 3
     * player2 is responsible for making turn = 3
     */

    if(this->itemAt(relativeOrigin,QTransform()) != NULL)
    {
       /**
         * Here the mouse returned an object of type QGraphicsItem, use its (x,y) position to do what you want
         * since we have several if statements, keep on checking for NULL at each if, since changing/removing the item will lose you the (x,y) you have
         * causing a segmentation fault when trying to get the (x,y) at the next if statement
         */



        /**
          * If it's the first turn and it's the turn of player 1, user here sees 2 of his cards, players 2 & 3 already saw their 2 cards
          * keep 1st card open till he chooses another card
          */

        if(FirstTurn && nbofFlips < 2 && this->itemAt(relativeOrigin,QTransform())->y() > 510.5)
        {
            QTextStream out(stdout);
            out << "hello" << this->itemAt(relativeOrigin,QTransform())->x() << " : " << this->itemAt(relativeOrigin,QTransform())->y() << endl;

            for(int i = 0 ; i < 4; i++)
            {
                /**
                  * If the player has pressed on a card in their hands that was not picked before, display this card.
                  */

                if(this->itemAt(relativeOrigin,QTransform())->x() == playerCards[i]->x && this->itemAt(relativeOrigin,QTransform())->y() == playerCards[i]->y && picked[i] == false)
                {
                    //playerCards[i]->setPixmap((QPixmap(QDir::currentPath() + "/Images/"+ QString::number(playerCards[i]->number) +".png")).scaled(80,100));
                    playerCards[i]->setPixmap((QPixmap(QDir::currentPath() + "/Images/"+ QString::number(c[0][i].first + c[0][i].second * 13 + 1) +".png")).scaled(80,100));
                    nbofFlips++;
                    picked[i] = true;
                    break;
                }
            }
        }





        /**
         * here the user either replaces one of his cards or places the card into the discard pile (toPile) or gets a choice card
         */

        if(this->itemAt(relativeOrigin,QTransform()) != NULL)
        {
            /**
             * puts card into discard pile
             */

            if(!FirstTurn && !special && choosing && turn == 1 && this->itemAt(relativeOrigin,QTransform())->y() == 387.5 && this->itemAt(relativeOrigin,QTransform())->x() == 600)
            {
                QTextStream out(stdout);
                out << this->itemAt(relativeOrigin,QTransform())->x() << " : " << this->itemAt(relativeOrigin,QTransform())->y() << endl;

                toPile->number = fromPile->number;
                fromPile->setPixmap((QPixmap(QDir::currentPath() + "/Images/CardBack.png")).scaled(125,125));
                toPile->setPixmap((QPixmap(QDir::currentPath() + "/Images/" + QString::number(toPile->number) + ".png")).scaled(80,100));

                choosing = false;

                drawn.push(pile.top());
                pile.pop();
                fromPile->number = pile.top().first + pile.top().second * 13 + 1;

                out << "her wer are bata: " << (toPile->number-1)%13 + 1 << endl;

                if ( (toPile->number-1)% 13 + 1 > 6 && (toPile->number-1)% 13 + 1 < 13)
                {
                    choosing = true;
                    special = true;
                }
                else
                {
                    turn = 2;
                }
            }



            /**
             * replaces card with one of his cards
             */

            else if (!special && !FirstTurn && choosing && turn == 1 && this->itemAt(relativeOrigin,QTransform())->y() > 510.5)
            {
                QTextStream out(stdout);

                for(int i = 0 ; i < 4 ; i++)
                {
                    if(this->itemAt(relativeOrigin,QTransform())->x() == playerCards[i]->x && this->itemAt(relativeOrigin,QTransform())->y() == playerCards[i]->y)
                    {
                        toPile->number = c[0][i].first + c[0][i].second * 13 + 1;

                        toPile->setPixmap((QPixmap(QDir::currentPath() + "/Images/" + QString::number(toPile->number) + ".png")).scaled(80,100));

                        playerCards[i]->number = fromPile->number;

                        /**
                         * @brief  Swaping a card from the player's hand with the card at top of the pile.
                         */

                        pair<int, int> temp = pile.top();
                        pile.pop();
                        fromPile->number = pile.top().first + pile.top().second * 13 + 1;
                        drawn.push(c[0][i]);
                        c[0][i] = temp;

                        out << "from: " << fromPile->number << " , " << "playerCards[" << i << "]: " << playerCards[i]->number << endl;

                        fromPile->setPixmap((QPixmap(QDir::currentPath() + "/Images/CardBack.png")).scaled(125,125));

                        choosing = false;
                        turn = 2;
                        break;
                    }
                }
            }



            /**
             * ******************************************************************** CHOICE CARDS ************************************************************************************
             */



            /**
             * Sees 1 of his cards
             */

            else if(special && !FirstTurn && choosing && turn == 1 && this->itemAt(relativeOrigin,QTransform())->y() > 510.5 && ((toPile->number - 1) % 13 + 1 == 7 || (toPile->number - 1) % 13 + 1 == 8))

            {
                for(int i = 0 ; i < 4 ; i++)
                {
                    if(this->itemAt(relativeOrigin,QTransform())->x() == playerCards[i]->x && this->itemAt(relativeOrigin,QTransform())->y() == playerCards[i]->y)
                    {
                        fromPile->setPixmap((QPixmap(QDir::currentPath() + "/Images/CardBack.png")).scaled(125,125));
                        playerCards[i]->setPixmap((QPixmap(QDir::currentPath() + "/Images/"+ QString::number(c[0][i].first + c[0][i].second*13 + 1) +".png")).scaled(80,100));

                        fate = true;
                        choosing = false;
                        special = false;
                        turn = 2;
                        toPile->number = fromPile->number;

                        /**
                          * Now discard the special card
                          */

                        drawn.push(pile.top());
                        pile.pop();
                        fromPile->number = pile.top().first + pile.top().second * 13 + 1;

                        turn = 2;
                        break;
                    }
                }

            }

            /**
              * Sees 1 card from other players
              */
            else if (special && !FirstTurn && choosing && turn == 1 && this->itemAt(relativeOrigin,QTransform())->y() < 370 && ((toPile->number - 1) % 13 + 1 == 9 || (toPile->number - 1) % 13 + 1 == 10))
            {


                for(int i = 4 ; i < 12; i++)
                {
                    if(this->itemAt(relativeOrigin,QTransform())->x() == playerCards[i]->x && this->itemAt(relativeOrigin,QTransform())->y() == playerCards[i]->y)
                    {
                        fromPile->setPixmap((QPixmap(QDir::currentPath() + "/Images/CardBack.png")).scaled(125,125));
                        playerCards[i]->setPixmap((QPixmap(QDir::currentPath() + "/Images/"+ QString::number(c[i/4][i%4].first + c[i/4][i%4].second * 13 +1) +".png")).scaled(80,100));

                        fate = true;
                        choosing = false;
                        special = false;
                        turn = 2;
                        toPile->number = fromPile->number;

                        /**
                          * Update memory arrays
                          */

                        if (i < 8) p[0]->memory1[i%4] = 1;
                        else p[0]->memory2[i%4] = 1;

                        turn = 2;
                        break;

                    }
                }

            }

            /**
             * swaps 2 cards
             */

            else if (special && !FirstTurn  && choosing && turn == 1 &&  ( (toPile->number - 1) % 13 + 1 == 11 || (toPile->number - 1) % 13 + 1 == 12) )
            {
                if(this->itemAt(relativeOrigin,QTransform()) != NULL)
                {
                        /**
                          * swap[0] = -1 := Player still didn't choose first card
                          */

                        if(swap[0] == -1)
                        {
                            for(int i = 0 ; i < 12; i++)
                            {
                                if(this->itemAt(relativeOrigin,QTransform())->x() == playerCards[i]->x && this->itemAt(relativeOrigin,QTransform())->y() == playerCards[i]->y)
                                {
                                    if(i < 4)
                                    {
                                        //playerCards[i]->setPixmap((QPixmap(QDir::currentPath() + "/Images/"+ QString::number(playerCards[i]->number) +".png")).scaled(80,100));
                                        swap[0] = i;

                                    }
                                    else
                                    {
                                        //playerCards[i]->setPixmap((QPixmap(QDir::currentPath() + "/Images/"+ QString::number(playerCards[i]->number) +".png")).scaled(80,100));
                                        swap[0] = i + 100;

                                    }
                                    break;

                                }
                            }
                        }

                        /**
                          * swap[0] != -1 and swap[1] = -1 --> Player has chosen first card but has not chosen second card yet.
                          * swap[i] > 100 --> Player has chosen a card from one of his opponents
                          */
                        else if (swap[1] == -1 && swap[0] != -1)
                        {
                                if(swap[0] > 100)
                                {
                                    for(int i = 0 ; i < 4; i++)
                                    {
                                        if(this->itemAt(relativeOrigin,QTransform())->x() == playerCards[i]->x && this->itemAt(relativeOrigin,QTransform())->y() == playerCards[i]->y)
                                        {
                                            //playerCards[i]->setPixmap((QPixmap(QDir::currentPath() + "/Images/"+ QString::number(playerCards[i]->number) +".png")).scaled(80,100));
                                            fromPile->setPixmap((QPixmap(QDir::currentPath() + "/Images/CardBack.png")).scaled(125,125));

                                            fate = true;

                                            swap[1] = i;
                                            swap[0] = swap[0] - 100;
                                            //QTextStream out(stdout);
                                            //out << "Before: " << playerCards[swap[0]]->number << " : " << playerCards[swap[1]]->number << endl;
                                            this->swapCards(swap[0],swap[1]);
                                            //out << "After: " << playerCards[swap[0]]->number << " : " << playerCards[swap[1]]->number << endl;

                                            swap[0] = swap[1] = -1;
                                            choosing = false;
                                            special = false;



                                            toPile->number = fromPile->number;
                                            drawn.push(pile.top());
                                            pile.pop();
                                            fromPile->number = pile.top().first + pile.top().second * 13 + 1;

                                            turn = 2;
                                            break;

                                        }
                                    }
                                }
                                /**
                                  * Player chose one of his cards first
                                  */
                                else
                                {
                                    for(int i = 4; i < 12; i++)
                                    {
                                        if(this->itemAt(relativeOrigin,QTransform())->x() == playerCards[i]->x && this->itemAt(relativeOrigin,QTransform())->y() == playerCards[i]->y)
                                        {
                                            //playerCards[i]->setPixmap((QPixmap(QDir::currentPath() + "/Images/"+ QString::number(playerCards[i]->number) +".png")).scaled(80,100));
                                            fromPile->setPixmap((QPixmap(QDir::currentPath() + "/Images/CardBack.png")).scaled(125,125));
                                            swap[1] = i;

                                            fate = true;

                                            QTextStream out(stdout);
                                            out << "Before: " << playerCards[swap[0]]->number << " : " << playerCards[swap[1]]->number << endl;
                                            this->swapCards(swap[0],swap[1]);

                                            out << "After: " << playerCards[swap[0]]->number << " : " << playerCards[swap[1]]->number << endl;

                                            swap[0] = swap[1] = -1;
                                            choosing = false;
                                            special = false;



                                            toPile->number = fromPile->number;
                                            drawn.push(pile.top());
                                            pile.pop();
                                            fromPile->number = pile.top().first + pile.top().second * 13 + 1;

                                            turn = 2;
                                            break;
                                        }
                                    }
                                }

                           }
                        }
                    }
                }


                /**
                 * here player is taking the card from the discard pile and replacing it by one of his own cards
                 */

                if(this->itemAt(relativeOrigin,QTransform()) != NULL)
                {

                    if(drawn.empty() && !FirstTurn && !choosing && turn == 1 && this->itemAt(relativeOrigin,QTransform())->y() == 387.5 && this->itemAt(relativeOrigin,QTransform())->x() == 600)
                    {
                        replacingD = true;
                    }
                    else if(drawn.empty() && !FirstTurn && !choosing && turn == 1 && this->itemAt(relativeOrigin,QTransform())->y() > 510.5 && replacingD == true)
                    {
                        for(int i = 0 ; i < 4 ; i++)
                        {
                            if(this->itemAt(relativeOrigin, QTransform())->x() == playerCards[i]->x && this->itemAt(relativeOrigin, QTransform())->y() == playerCards[i]->y)
                            {
                                toPile->number = c[0][i].first + c[0][i].second * 13 + 1;

                                pair<int, int> pi = drawn.top();
                                drawn.pop();
                                c[0][i] = pi;
                                drawn.push(pi);

                                playerCards[i]->number = pi.first + pi.second*13 + 1;
                                replacingD = false;
                                turn = 2;
                                break;
                            }
                        }
                    }

                }



        }



    if(this->itemAt(relativeOrigin,QTransform()) != NULL)
    {
        if(this->itemAt(relativeOrigin,QTransform())->x() == 800 && this->itemAt(relativeOrigin,QTransform())->y() == 800)
        {

            deleted = true;



        }
    }

    if(this->itemAt(relativeOrigin,QTransform()) != NULL)
    {
        if(this->itemAt(relativeOrigin,QTransform())->x() == 0 && this->itemAt(relativeOrigin,QTransform())->y() == 400)
        {
            this->cabo = true;
            this->g2_end();
        }
    }

    if(this->itemAt(relativeOrigin,QTransform()) != NULL)
    {
        /**
         * Here user gets to see what is at the top of the deck (fromPile)
         */

        if (!special && !FirstTurn && this->itemAt(relativeOrigin,QTransform())->y() == 387.5 && turn == 1 && !choosing && this->itemAt(relativeOrigin,QTransform())->x() == 387.5)
        {
            QTextStream out(stdout);
            out << this->itemAt(relativeOrigin,QTransform())->x() << " : " << this->itemAt(relativeOrigin,QTransform())->y() << endl;

            int x = pile.top().first + pile.top().second * 13;
            //x = 11;
            fromPile->number = x + 1;
            fromPile->setPixmap((QPixmap(QDir::currentPath() + "/Images/"+ QString::number(x + 1) +".png")).scaled(80,100));

            choosing = true;

        }
    }

    if (turn == 2)
    {


        //g2_end();
        text->setPlainText("Turn of Player 2\n");
        initial();
        QTimer::singleShot(2000, this, SLOT(player2turn()));
    }


}



/**
 * @brief game2_scene::startingTurn lets p[1] & p[2] see 2 of their cards, the process is random (No difficulity levels)
 */

void game2_scene :: startingTurn()
{
        /**
         * @brief Generate a random pair of distinct numbers between 0 & 3 inclusive
         */
        for (int i = 0; i < 2; i++)
        {
            set <int> myset;

            for (int i = 0; i < 4; i++) myset.insert(i);

            int x = rand()%4;
            myset.erase(x);

            int y, temp = rand()%3;

            for (auto it : myset)
            {
                if(temp == 0)
                {
                    y = it;
                    break;
                }
                temp--;
            }

            cout << x << "*" << y << "\n";
            p[i+1]->card[x] = 1;
            p[i+1]->card[y] = 1;
        }

}



void game2_scene :: update()
{

    if(nbofFlips == 2)
    {
        //+1 to nbofFLips since we dont use it again and it stays at 2 which will keep this looping
        nbofFlips ++;
        FirstTurn = false;
        timer->start(4000);
    }

    if(fate)
    {
        timer->start(4000);
        fate = false;
    }
}



void game2_scene :: swapCards(int first, int second)
{
    if (first < 0 || first >= 12 || second < 0 || second >= 12) return;
    int temp = playerCards[first]->number;
    playerCards[first]->number = playerCards[second]->number;
    playerCards[second]->number = temp;

    if(first < 4)
    {
        c[0][first].first = playerCards[first]->number%13+1;
        c[0][first].second = playerCards[first]->number/13;
    }
    else if ( first >4 && first < 8)
    {
        c[1][first-4].first = playerCards[first]->number%13+1;
        c[1][first-4].second = playerCards[first]->number/13;

    }
    else
    {
        c[2][first-8].first = playerCards[first]->number%13+1;
         c[2][first-8].second = playerCards[first]->number/13;
    }

    if(second < 4)
    {
        c[0][second].first = playerCards[second]->number%13+1;
         c[0][second].second = playerCards[second]->number/13;
    }
    else if ( second >4 && second < 8)
    {
        c[1][second-4].first = playerCards[second]->number%13+1;
        c[1][second-4].second = playerCards[second]->number/13;
    }
    else
    {
        c[2][second-8].first = playerCards[second]->number%13+1;
        c[2][second-8].second = playerCards[second]->number/13;
    }

    if(first < 4)
    {
        playerCards[first]->y = playerCards[first]->y - 50;
        playerCards[second]->y = playerCards[second]->y + 50;
        playerCards[first]->setPos(playerCards[first]->x,playerCards[first]->y);
        playerCards[second]->setPos(playerCards[second]->x,playerCards[second]->y);
    }

    else
    {
        playerCards[first]->y = playerCards[first]->y + 50;
        playerCards[second]->y = playerCards[second]->y - 50;
        playerCards[first]->setPos(playerCards[first]->x,playerCards[first]->y);
        playerCards[second]->setPos(playerCards[second]->x,playerCards[second]->y);
    }

    un = first;
    deux = second;
    //playerCards[i]->setPos(playerCards[i]->x,playerCards[i]->y);
    QTimer::singleShot(2000, this, SLOT(ReactToSwap()));
    //QTimer::singleShot(2000, this, SLOT(player3turn()));

}




void game2_scene :: player2turn()
{


        if (turn != 2 || pile.empty() || cabo) return;
        push->setValue(25);


        int value, playervalue;
        bool foundless = false, foundlessfrom = false;


        value = (toPile->number - 1) % 13 + 1;

        QTextStream out(stdout);
        out << "PLAYER2: Top Card (from): " << (fromPile->number -1)%13 + 1 << ", ToPile top Card: " << value << endl;
        for(int i = 4; i < 8; i++)
        {
            out << "Value known " << i-4 << " " <<  c[1][i-4].first + 1 << "**" << p[1]->card[i-4] << endl;
        }
        if(!drawn.empty())
        {
            /**
             * Player can draw from the drawn
             * take from drawn if less than what he knows he has, else discard
             */



            for(int i = 4; i < 8; i++)
            {
                 if(p[1]->card[i-4] != -1)
                 {
                playervalue = c[1][i-4].first + 1;

                if(value < playervalue)
                {
                    drawn.pop();
                    drawn.push(c[1][i-4]);

                    int temp = toPile->number;
                    toPile->number = playerCards[i]->number;
                    playerCards[i]->number = temp;

                    c[1][i-4].first = (playerCards[i]->number - 1) % 13;
                    c[1][i-4].second = (playerCards[i]->number - 1) / 13;

                    //if(i < 8)  ::::: IT WAS 4 NOT SURE OF IT

                    playerCards[i]->y = playerCards[i]->y + 50;
                    playerCards[i]->setPos(playerCards[i]->x,playerCards[i]->y);

                    single = i;
                    QTimer::singleShot(1000, this, SLOT(ReactToSwapOne()));

                    toPile->setPixmap((QPixmap(QDir::currentPath() + "/Images/" + QString::number(toPile->number) + ".png")).scaled(80,100));
                    foundless = true;

                    turn = 4;
                    break;
                }
            }
            }
        }

        if(drawn.empty() || !foundless)
        {

            fromPile->number = pile.top().first + pile.top().second * 13 + 1;

            value = pile.top().first + 1;



            /**
             * decide if to take card or not
             */

            if(value < 7 || value == 13)
            {

                for(int i = 4; i < 8; i++)
                {
                    if(p[1]->card[i-4] != -1)
                    {
                    playervalue = c[1][i-4].first + 1;

                    if(value < playervalue)
                    {
                        /**
                          * take from pile
                          */


                        int temp = fromPile->number;
                        fromPile->number = playerCards[i]->number;
                        playerCards[i]->number = temp;

                        c[1][i-4].first = (playerCards[i]->number-1) % 13;
                        c[1][i-4].second = (playerCards[i]->number-1) / 13;

                        foundlessfrom = true;

                        toPile->number = fromPile->number;
                        drawn.push(pile.top());
                        pile.pop();
                        fromPile->number = pile.top().first + pile.top().second * 13 + 1;

                        playerCards[i]->y = playerCards[i]->y + 50;
                        playerCards[i]->setPos(playerCards[i]->x,playerCards[i]->y);

                        single = i;

                        QTimer::singleShot(1000, this, SLOT(ReactToSwapOne()));

                        toPile->setPixmap((QPixmap(QDir::currentPath() + "/Images/" + QString::number(toPile->number) + ".png")).scaled(80,100));

                        turn = 4;
                        break;
                    }
                    }
                }

                if(!foundlessfrom)
                {
                    /**
                      * discard card
                      */
                    toPile->number = fromPile->number;
                    drawn.push(pile.top());
                    pile.pop();
                    fromPile->number = pile.top().first + pile.top().second * 13 + 1;
                    //toPile->number = drawn.top();
                    toPile->setPixmap((QPixmap(QDir::currentPath() + "/Images/" + QString::number(toPile->number) + ".png")).scaled(80,100));
                    turn = 4;
                }

            }



            /**
             * see own card
             */

            else if (value > 6 && value < 9)
            {
                /**
                  * See the first unknown card in his hand from left to right
                  */

                for(int i = 4; i < 8 ; i++)
                {
                    if(p[1]->card[i-4] == -1)
                    {
                        p[1]->card[i-4] = 1;

                        break;
                    }
                }
                turn = 4;
            }



            /**
             * see opponent's card
             */

            else if(value > 8 && value < 11)
            {

                /**
                  * Check from left to right opponent cards alternating between opponents untill player 2 finds an unknown card: seet it then break
                  */

                for(int i = 0 ; i < 4; i++)
                {
                    if(p[1]->memory1[i] == -1)
                    {
                        p[1]->memory1[i] = 1;
                        break;
                    }

                    if(p[1]->memory2[i] == -1)
                    {
                        p[1]->memory2[i] = 1;
                        break;
                    }
                }


                toPile->number = fromPile->number;
                drawn.push(pile.top());
                pile.pop();
                fromPile->number = pile.top().first + pile.top().second * 13 + 1;

                turn = 4;
                toPile->setPixmap((QPixmap(QDir::currentPath() + "/Images/" + QString::number(toPile->number) + ".png")).scaled(80,100));

            }
            else if (value == 11 || value == 12)
            {
                /**
                 * check for every known card of player2 with every known card from other players, known by player 2, compare and swap if less then break
                 * Player 3 strategy is better
                 *
                 */

                bool find = false;

                for (int i = 0; i < 4; i++)
                {
                    if (p[1]->card[i] == -1) continue;

                    for(int j = 0; j < 4; j++)
                    {
                        if (p[1]->memory1[j] == 1 && c[0][j].first  < c[1][i].first)
                        {
                            pair<int, int> temp = c[0][j];
                            c[0][j] = c[1][i];
                            c[1][i] = temp;

                            find = true;
                            i = 4;
                            break;
                        }

                        if (p[1]->memory2[j] == 1 && c[2][j].first < c[1][i].first)
                        {
                            pair<int,int> temp = c[2][j];
                            c[2][j] = c[1][i];
                            c[1][i] = temp;
                            find = true;
                            i = 4;
                            break;
                        }
                    }
                }

                if (!find)
                {
                    /**
                      * Swap randomly
                      */
                    int x = rand() % 2;
                    if (x == 1) x = 2;
                    int y = rand()%4;
                    pair<int, int> temp = c[1][y];
                    c[1][y] = c[x][y];
                    c[x][y] = temp;
                }

                toPile->number = fromPile->number;
                drawn.push(pile.top());
                pile.pop();
                fromPile->number = pile.top().first + pile.top().second * 13 + 1;

                turn = 4;
                toPile->setPixmap((QPixmap(QDir::currentPath() + "/Images/" + QString::number(toPile->number) + ".png")).scaled(80,100));

            }

        }

         /**
          * End Turn 2
          */

        if (turn == 4)
        {
            // this needs to be edited to the known values only

            int sum = 0;
            int known = 0;
            for(int i = 0 ; i < 4 ; i++)
            {
                if(p[1]->card[i] != -1)
                {
                    sum = sum + c[1][i].first;
                    known += 1;
                }
            }
            if((sum <= 10 && known == 4) || (sum <= 3 && known >= 2))
            {

                cabo = true;
            }
            g2_end();
            text->setPlainText("Turn of Player 3\n");
            initial();
            turn = 3;
            QTimer::singleShot(3000, this, SLOT(player3turn()));
        }

}

void game2_scene :: player3turn()
{

        if (turn != 3 || pile.empty() || cabo) return;

        push->setValue(50);

        int value, playervalue;
        bool foundless = false, foundlessfrom = false;

        value = (toPile->number-1) % 13 + 1;
        QTextStream out(stdout);
        out << "PLAYER3: Top Card (from): " << (fromPile->number -1)%13 + 1 << ", ToPile top Card: " << value << endl;
        for(int i = 8; i < 12; i++)
        {
            out << "Value known " << i-8 << " " <<  c[2][i-8].first + 1 << "**" << p[2]->card[i-8] <<   endl;
        }
        if(!drawn.empty())
        {
            /**
             * take from drawn if less than what he knows he has
             */



            for(int i = 8; i < 12; i++)
            {
                 if(p[2]->card[i-8] != -1)
                 {
                playervalue = c[2][i-8].first + 1;

                if(value < playervalue)
                {
                    int temp = toPile->number;
                    toPile->number = playerCards[i]->number;
                    playerCards[i]->number = temp;

                    drawn.pop();
                    drawn.push(c[2][i-8]);
                    c[2][i-8].first = (playerCards[i]->number-1) % 13;
                    c[2][i-8].second = (playerCards[i]->number-1) / 13;

                    //if(i < 8)  ::::: IT WAS 4 NOT SURE OF IT

                    playerCards[i]->y = playerCards[i]->y + 50;
                    playerCards[i]->setPos(playerCards[i]->x,playerCards[i]->y);

                    single = i;
                    QTimer::singleShot(2000, this, SLOT(ReactToSwapOne()));

                    toPile->setPixmap((QPixmap(QDir::currentPath() + "/Images/" + QString::number(toPile->number) + ".png")).scaled(80,100));
                    foundless = true;
                    turn = 1;
                    break;
                }
            }
            }
        }


        if(drawn.empty() || !foundless)
        {

            fromPile->number = pile.top().first + pile.top().second * 13 + 1;

            value = (fromPile->number - 1) % 13 + 1;



            /**
             * decide if to take card or not
             */

            if(value < 7 || value == 13)
            {

                for(int i = 8; i < 12; i++)
                {
                    if(p[2]->card[i-8] != -1)
                    {
                    playervalue = c[2][i-8].first + 1;

                    if(value < playervalue)
                    {
                        int temp = fromPile->number;
                        fromPile->number = playerCards[i]->number;
                        playerCards[i]->number = temp;

                        c[2][i-8].first = (playerCards[i]->number-1) % 13;
                        c[2][i-8].second = (playerCards[i]->number-1) / 13;

                        foundlessfrom = true;

                        toPile->number = fromPile->number;
                        drawn.push(make_pair((toPile->number - 1) % 13, (toPile->number - 1) /13));
                        pile.pop();
                        fromPile->number = pile.top().first + pile.top().second * 13 + 1;

                        playerCards[i]->y = playerCards[i]->y + 50;
                        playerCards[i]->setPos(playerCards[i]->x, playerCards[i]->y);

                        single = i;

                        QTimer::singleShot(1000, this, SLOT(ReactToSwapOne()));

                        toPile->setPixmap((QPixmap(QDir::currentPath() + "/Images/" + QString::number(toPile->number) + ".png")).scaled(80,100));
                        turn = 1;

                        break;
                    }
                    }
                }

                if(!foundlessfrom)
                {
                    toPile->number = fromPile->number;
                    drawn.push(pile.top());
                    pile.pop();
                    fromPile->number = pile.top().first + pile.top().second * 13 + 1;

                    toPile->setPixmap((QPixmap(QDir::currentPath() + "/Images/" + QString::number(toPile->number) + ".png")).scaled(80,100));
                    turn = 1;
                }

            }



            /**
             * see own card
             */

            else if (value > 6 && value < 9)
            {
                /**
                  * See the first unknown card in his hand from left to right
                  */

                for(int i = 8; i < 12 ; i++)
                {
                    if(p[2]->card[i-8] == -1)
                    {
                        p[2]->card[i-8] = 1;

                        break;
                    }
                }
                turn = 1;
            }



            /**
             * see opponent's card
             */

            else if(value > 8 && value < 11)
            {

                /**
                  * Check from right to left opponent cards alternating between opponents untill player 2 finds an unknown card: seet it then break
                  */

                for(int i = 3; i >= 0; i--)
                {
                    if(p[2]->memory1[i] == -1)
                    {
                        p[2]->memory1[i] = 1;
                        break;
                    }

                    if(p[2]->memory2[i] == -1)
                    {
                        p[2]->memory2[i] = 1;
                        break;
                    }
                }


                toPile->number = fromPile->number;
                drawn.push(pile.top());
                pile.pop();
                fromPile->number = pile.top().first + pile.top().second * 13 + 1;


                toPile->setPixmap((QPixmap(QDir::currentPath() + "/Images/" + QString::number(toPile->number) + ".png")).scaled(80,100));
                turn = 1;

            }
            else if (value == 11 || value == 12)
            {
                /**
                 * Swap the minimum opponent card that he knows with his maximum card that he knows
                 *
                 */

                int  maxi = 0, mini = 14, ind_maxi = -1, ind_mini = -1;
                bool where = false;
                for (int i = 0; i < 4; i++)
                {
                    if (p[2]->card[i] == 1 && c[2][i].first + 1 > maxi)
                    {
                        maxi = c[2][i].first + 1;
                        ind_maxi = i;
                    }

                    if (p[2]->memory1[i] == 1 && c[0][i].first + 1 < mini)
                    {
                        mini = c[0][i].first + 1;
                        ind_mini = i;
                        where = true;
                    }

                    if (p[2]->memory2[i] == 1 && c[1][i].first + 1 < mini)
                    {
                        mini = c[1][i].first + 1;
                        ind_mini = i;
                    }

                }

                if (maxi > 0 && mini < 14)
                {
                    int x = 1;
                    if (where) x = 0;
                    pair<int,int> temp = c[2][ind_maxi];
                    c[2][ind_maxi] = c[x][ind_mini];
                    c[x][ind_mini] = temp;
                }

                else
                {
                    /**
                      * Swap randomly
                      */
                    int x = rand()%2, y = rand()%4;
                    pair<int, int> temp = c[2][y];
                    c[2][y] = c[x][y];
                    c[x][y] = temp;

                }
                toPile->number = fromPile->number;
                drawn.push(pile.top());
                pile.pop();
                fromPile->number = pile.top().first + pile.top().second * 13 + 1;

                toPile->setPixmap((QPixmap(QDir::currentPath() + "/Images/" + QString::number(toPile->number) + ".png")).scaled(80,100));
                turn = 1;

            }

        }

         /**
          * End Turn 3
          */


        push->setValue(100);

        if (turn == 1)
        {
            int sum = 0;
            int known = 0 ;
            for(int i = 0 ; i < 4 ; i++)
            {
                if(p[2]->card[i] != -1)
                {
                    sum = sum + c[2][i].first;
                    known += 1;
                }
            }
            if(sum <= 8 && known >= 3)
            {
                cabo = true;
            }
            this->g2_end();
            text->setPlainText("Turn of Player 1\n");
            initial();
        }

}


void game2_scene :: ReactToSwap()
{
    /**
      * 2 cards
      */

    if(un >= 0 && un < 4  && deux >= 0 && deux < 12)
    {
        playerCards[un]->y = playerCards[un]->y + 50;
        playerCards[deux]->y = playerCards[deux]->y - 50;
        playerCards[un]->setPos(playerCards[un]->x,playerCards[un]->y);
        playerCards[deux]->setPos(playerCards[deux]->x,playerCards[deux]->y);


    }

    else if(un >= 0 && un < 12 && deux >= 0 && deux < 12)
    {
        playerCards[un]->y = playerCards[un]->y - 50;
        playerCards[deux]->y = playerCards[deux]->y + 50;
        playerCards[un]->setPos(playerCards[un]->x,playerCards[un]->y);
        playerCards[deux]->setPos(playerCards[deux]->x,playerCards[deux]->y);
    }

    un = deux = -1;
}

void game2_scene :: ReactToSwapOne()
{
    /**
      * 1 card
      */

    if(single < 4 && single >= 0)
    {
        playerCards[single]->y = playerCards[single]->y + 50;
        playerCards[single]->setPos(playerCards[single]->x,playerCards[single]->y);

    }

    else if(single >= 0 && single < 12)
    {
        playerCards[single]->y = playerCards[single]->y - 50;
        playerCards[single]->setPos(playerCards[single]->x,playerCards[single]->y);
    }

    single = -1;
}

void  game2_scene :: initial()
{

    choosing = replacingD = false;

    for(int i = 0 ; i < 4 ; i++)
    {
        picked[i] = false;
    }

}

void  game2_scene ::g2_end()
{
    if (cabo || pile.empty())
    {

        s[0] = s[1] = s[2] = 0;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                s[i] += c[i][j].first;
            }
        }
        if (s[0] < s[1] && s[0] < s[2]) winner = 1;
        else if (s[1] < s[0] && s[1] < s[2]) winner = 2;
        else if (s[2] < s[1] && s[2] < s[0]) winner = 3;
        else if(s[0] > s[1] && s[0] > s[2]) winner = 4;  // tie 2-3
        else if(s[1] > s[0] && s[1] > s[2]) winner = 5;  // tie 1-3
        else if(s[2] > s[1] && s[2] > s[0]) winner = 6;  // tie 2-1
        else winner = 7; //all tie

        for (int i = 0; i < 12; i++)
        {
            playerCards[i]->setPixmap((QPixmap(QDir::currentPath() + "/Images/"+ QString::number(c[i/4][i%4].first + c[i/4][i%4].second*13 + 1) +".png")).scaled(80,100));
        }
    }
}











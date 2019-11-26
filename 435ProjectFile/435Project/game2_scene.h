#ifndef GAME2_SCENE_H
#define GAME2_SCENE_H

#include <QGraphicsScene>
#include <cards.h>
#include <QString>
#include <QWidget>
#include <QtWidgets>
#include <QObject>
#include <viewgametwo.h>
#include <QTimer>
#include <QMouseEvent>
#include <vector>
#include <stack>
#include <g2_player.h>
#include <set>
using namespace std;


class game2_scene : public QGraphicsScene
{
     Q_OBJECT

private:
   void mousePressEvent(QGraphicsSceneMouseEvent *event);
public:

    game2_scene();

    /**
     * @brief pile is the stack of cards at the center of the scene, not discarded or taken yet.
     * @brief drawn is the satck of discarded cards.
     */
    stack< pair<int, int> > pile, drawn;

    /**
     * @brief p is an array of 3 players where p[i] is player i
     */
    g2_player * p[3];

    /**
     * @brief turn indicates the index of the player whose turn is now
     */
    int turn;

    /**
     * @brief c[i][j] is the number of the card j in the hand of player i
     * to generate the number do c[i][j].first + c[i][j] * 13 + 1;
     */
    pair<int, int> c[3][4];


    vector <Cards*> playerCards;
    Cards * fromPile, * toPile;
    ViewGameTwo * Game2_View;
    QString user;
    QTimer * timer, *timer1, * player2timer, * player3timer, * delaytimer;
    QProgressBar *push;
    QGraphicsPixmapItem * exitB;

    /**
     * @brief FirstTurn is true if we're in the first turn in the game
     */
    bool FirstTurn;
    int nbofFlips;
    int swap[2];

    int AllowedFlips;
    /**
     * @brief fate is true to go back to initial state after a certain time.
     * @brief piledUp is false if the drawn is empty
     * @brief choosing is true when the user draws a card from the pile
     * @brief started is true if ...
     */
    bool started, choosing, piledUp, fate;
    bool replacingD, delay1, delay2, up, down;

    /**
     * @brief picked is used to prevent the player from selecting the same card twice.
     */
    bool picked[4];

    
    int un, deux, single;

    /**
     * @brief text is used to display which player is playing now
     */
    QGraphicsTextItem * text;

public slots:

    void setUser(QString a);
    void startingTurn();
    void change();
    void update();
    void swapCards(int first, int second);
    void player2turn();
    void player3turn();
    void delayfunc();
    void ReactToSwap();
    void ReactToSwapOne();
    void initial();

};

#endif // GAME2_SCENE_H

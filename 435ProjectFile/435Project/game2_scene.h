#ifndef GAME2_SCENE_H
#define GAME2_SCENE_H

#include <QGraphicsScene>
#include <cards.h>
#include <QString>
//#include <QCloseEvent>
#include <QWidget>
#include <QtWidgets>
#include <QObject>
#include <viewgametwo.h>
#include <QTimer>
#include <QMouseEvent>
#include <vector>
using namespace std;





class game2_scene : public QGraphicsScene
{
     Q_OBJECT

private:
   void mousePressEvent(QGraphicsSceneMouseEvent *event);
public:

    game2_scene();
    vector <Cards*> playerCards;
    Cards * fromPile, * toPile;
    ViewGameTwo * Game2_View;
    QString user;
    QTimer * timer, *timer1;
    QProgressBar *push;

    int pile[52], drawn[52], AllowedFlips, nbofFlips, player2[4], player3[4];
    bool started, FirstTurn, choosing, piledUp;

    bool turn1, turn2, turn3;


public slots:

    void setUser(QString a);
    void change();
    void update();



};

#endif // GAME2_SCENE_H

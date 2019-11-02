#ifndef DICE_H
#define DICE_H

#include <QWidget>
#include <QObject>
#include <QtWidgets>
#include <strings.h>
#include <mainscreen.h>
#include <game1_scene.h>
#include <players.h>
//#include <starter.h>
/**
  *\file Dice.h
  */

class dice : public QWidget
{
    Q_OBJECT

private:
     void closeEvent(QCloseEvent *bar);
public:
    explicit dice(QWidget *parent = 0);
    QPushButton * ThrowBlue_Button, * EndTurn_Button, * EndGame_Button; //* ThrowRed_Button,
    QGridLayout * Horizental;
    QLabel * PlayerUsername, * error , * choose;
    QRadioButton * blue, * red;
    QVBoxLayout * VerticalDice, * VerticalRadioB, *Vertical;
    game1_scene * Game1Scene;
    QGraphicsView * Game1_View;
    MainScreen * BackToMain;
    int blueval, redval;
    QString user, name;
    QTimer * timer ,* timer1, *timerPC;
    QGroupBox * GP;
    bool endedturn, taketurns, other, endedturnPC, once, isResume; //endedturn is used to let the user throw the die only once, taketurns is used to give the PC 1 turn
                                                    //other is used switch between user(player1) and player2
                                                     //endedturnPC is used to give plauer1 his throw button when PC is done
    int difficulty, startingPlayer;  //difficulty determines what algorythm takes place and if player2 is human or PC
                                    //startingPlayer determines if player1 or player2 starts the round


signals:

public slots:

    void ThrowBlue();
    void ThrowBluePC();
    void EndTurn();
    void EndGame ();
    void SetUser(QString d, QString n, int s, int w, bool h);
    void reveal();
    //void listener();
    void EndTurnPC();
    void listener();
    void wonturn();



};

#endif // DICE_H

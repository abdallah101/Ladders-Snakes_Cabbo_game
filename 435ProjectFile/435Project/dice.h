#ifndef DICE_H
#define DICE_H

#include <QWidget>
#include <QObject>
#include <QtWidgets>
#include <strings.h>
#include <mainscreen.h>
#include <game1_scene.h>
#include <players.h>
/**
  *\file Dice.h
  */

class dice : public QWidget
{
    Q_OBJECT
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
    QTimer * timer ,* timer1;
    QGroupBox * GP;
    bool endedturn;
    int difficulty;

signals:

public slots:

    void ThrowBlue();
    //void ThrowRed();
    void EndTurn();
    void EndGame ();
    void SetUser(QString d, QString n);
    void reveal();


};

#endif // DICE_H

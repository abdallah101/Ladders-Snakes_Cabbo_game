#ifndef DICE_H
#define DICE_H

#include <QWidget>
#include <QObject>
#include <QtWidgets>
#include <strings.h>
#include <mainscreen.h>
#include <game1_scene.h>
/**
  *\file Dice.h
  */

class dice : public QWidget
{
    Q_OBJECT
public:
    explicit dice(QWidget *parent = 0);
    QPushButton * ThrowBlue_Button, * ThrowRed_Button,* EndTurn_Button, * EndGame_Button;
    QGridLayout * Horizental;
    QLabel * PlayerUsername, * blue, * red;
    QVBoxLayout * VerticalDice;
    game1_scene * Game1Scene;
    QGraphicsView * Game1_View;
    MainScreen * BackToMain;
    int blueval, redval;
signals:

public slots:

    void ThrowBlue();
    void ThrowRed();
    void EndTurn();
    void EndGame ();

};

#endif // DICE_H

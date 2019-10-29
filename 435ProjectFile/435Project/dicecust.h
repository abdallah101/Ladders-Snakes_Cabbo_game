#ifndef DICECUST_H
#define DICECUST_H

#include <QWidget>
#include <QObject>
#include <QtWidgets>
#include <strings.h>
#include <mainscreen.h>
#include <game1_scene.h>
#include <game1_scenecust.h>

/**
  *\file diceCust.h
  */


class diceCust : public QWidget
{
    Q_OBJECT
public:
    explicit diceCust(QWidget *parent = 0);
    QPushButton * ThrowBlue_ButtonCust, * ThrowRed_ButtonCust,* EndTurn_ButtonCust, * EndGame_ButtonCust;
    QGridLayout * HorizentalCust;
    QLabel * PlayerUsernameCust, * blueCust, * redCust;
    QVBoxLayout * VerticalDiceCust;
    game1_sceneCust * Game1Cust;
    QGraphicsView * Game1_ViewCust;
    MainScreen * BackToMainCust;
    int bluevalCust, redvalCust;
    QString user;



signals:

public slots:

    void ThrowBlueCust();
    void ThrowRedCust();
    void EndTurnCust();
    void EndGameCust();
    void SetUser(QString d);


};
#endif // DICECUST_H

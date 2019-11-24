#ifndef GAME2DETAILS_H
#define GAME2DETAILS_H

#include <QWidget>
#include <QObject>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
/**
  *\file game2details.h
  */

class game2details : public QWidget
{
    Q_OBJECT

private:

public:
    explicit game2details(QWidget *parent = 0);
    QLabel * G2_Actions, * G2_TurnOf;
    QPushButton * G2_EndTurn;
    QGridLayout * G2_H;

public slots:
    void PlayerTurn(int);
};


#endif // GAME2DETAILS_H

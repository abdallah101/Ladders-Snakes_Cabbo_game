#ifndef GAMEONE_H
#define GAMEONE_H

#include <QObject>
#include <QGraphicsScene>
#include <QPushButton>
#include <QGridLayout>
#include <QString>
#include <custWid.h>
#include <dice.h>
#include <game1_modes.h>
#include <QTimer>
#include <starter.h>

class MainScreen; //forward declaration

class GameOne : public QWidget
{
    Q_OBJECT
public:
    explicit GameOne(QWidget *parent = 0);
    QPushButton * startButton, * SetLaddersSnakes, *resume, * GoBack;
    //GameOne();
    Starter * scene;
    dice * scene2;
    QGridLayout * Horiz;
    QString user, name; //username and first name
    custWid * scene1;
    QRadioButton * easy, *medium, *hard, *twoplayers;
    QRadioButton * easyC, *mediumC, *hardC, * twoplayersC;
    QLabel * choose, * error;
    QTimer * timer;
    QVBoxLayout * VerticalRadioB, * VerticalRadioBC;
    QGroupBox * GP, * GPC;
    MainScreen * sc;



signals:

public slots:

    void start();
    void customize();
    void SetUser(QString d, QString n);
    void update();
    void resumegame();
    void back();

};

#endif // GAMEONE_H

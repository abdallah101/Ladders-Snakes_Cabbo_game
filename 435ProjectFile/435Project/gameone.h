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
class GameOne : public QWidget
{
    Q_OBJECT
public:
    explicit GameOne(QWidget *parent = 0);
    QPushButton * startButton, * SetLaddersSnakes;
    //GameOne();
    Game1_Modes * scene;
    QGridLayout * Horiz;
    QString user, name;
    custWid * scene1;


signals:

public slots:

    void start();
    void customize();
    void SetUser(QString d, QString n);

};

#endif // GAMEONE_H

#ifndef GAME1_SCENE_H
#define GAME1_SCENE_H
#include <QGraphicsScene>
#include <players.h>
#include <QTimer>
#include <QString>

/**
  *\file game1_scene.h
  */

class game1_scene : public QGraphicsScene
{
  Q_OBJECT
public:
    game1_scene();
    players * player1, * player2;

    int grid[100];
    QString user;
    QString startingplayer;
    int diff;//takes difficulty from dice
    bool isResume, isCust;




public slots:
    void check (players * player);
    void Move(players * , int);
    void SetUser(QString a, QString b, int c, bool d, bool z); //needs better naming for later!!
    void AddLadderSnake(int cellFrom, int cellTo);




};

#endif // GAME1_SCENE_H

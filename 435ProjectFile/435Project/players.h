#ifndef PLAYERS_H
#define PLAYERS_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

class players : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit players(QObject *parent = nullptr);
    int cell;
    double limit, limitup, limitback, maxY, maxX, ratioY;
    QTimer * timer, * timerLS;
    bool active; //gives other widgets info that there is a process currently working
    int steps;
    bool notFirst; //since to my misfortune, there is a ladder on 0 and 0 is a possible die roll :D
    bool myturn; //to determine which player chooses the die this round

public slots:
    void MoveUp();
    void activate();
    void MoveRight();
    void MoveLeft();
    void activateRight();
    void activateLeft();
    void MoveP(int);
    int FindCell();
    void MovePExtra(int);
    void MovePCust(int);
    void activateRU();
    void MoveRU();
    void activateLU();
    void MoveLU();
    void activateLUR();
    void activateRUL();
    void MoveLUR();
    void MoveRUL();
    void MoveDown();
    void activateMoveDown();
    void activateLadderUR();
    void activateLadderUL();
    void activateSnakeDL();
    void activateSnakeDR();
    void LadderUR();
    void LadderUL();
    void SnakeDR();
    void SnakeDL();
    void activateLR();
    void MoveLR();


};

#endif // PLAYERS_H

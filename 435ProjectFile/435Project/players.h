#ifndef PLAYERS_H
#define PLAYERS_H

#include <QGraphicsPixmapItem>
#include <QObject>

class players : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit players(QObject *parent = nullptr);
    int cell;
    void MoveP(int);
    int FindCell();
    void MovePExtra(int);
};

#endif // PLAYERS_H

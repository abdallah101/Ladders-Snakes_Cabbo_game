#ifndef CARDS_H
#define CARDS_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Cards : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Cards();
    int number;
};

#endif // CARDS_H

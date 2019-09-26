#ifndef RUBBISH_H
#define RUBBISH_H

#include <QObject>
#include <QGraphicsPixmapItem>

class rubbish : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit rubbish(QObject *parent = 0);

signals:

public slots:

    void raining ();
    void godown();

};

#endif // RUBBISH_H

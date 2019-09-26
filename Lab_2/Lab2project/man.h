#ifndef MAN_H
#define MAN_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>

class man : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit man(QObject *parent = 0);

signals:

public slots:


    void keyPressEvent (QKeyEvent * event);

};

#endif // MAN_H

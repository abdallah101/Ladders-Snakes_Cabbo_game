#ifndef GAMEONE_H
#define GAMEONE_H

#include <QObject>
#include <QGraphicsScene>
#include <QPushButton>
#include <QGridLayout>
class GameOne : public QWidget
{
    Q_OBJECT
public:
    explicit GameOne(QWidget *parent = 0);
    QPushButton * startButton;
    //GameOne();
    QWidget * scene;
    QGridLayout * Horiz;

signals:

public slots:

    void start();

};

#endif // GAMEONE_H

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
class GameOne : public QWidget
{
    Q_OBJECT
public:
    explicit GameOne(QWidget *parent = 0);
    QPushButton * startButton, * SetLaddersSnakes;
    //GameOne();
    dice * scene;
    QGridLayout * Horiz;
    QString user, name;
    custWid * scene1;
    QRadioButton * easy, *medium, *hard, *twoplayers;
    QLabel * choose, * error;
    QTimer * timer;
    QVBoxLayout * VerticalRadioB ;
    QGroupBox * GP;


signals:

public slots:

    void start();
    void customize();
    void SetUser(QString d, QString n);
    void update();

};

#endif // GAMEONE_H

#ifndef STARTER_H
#define STARTER_H

#include <QWidget>
#include <QObject>
#include <QApplication>
#include <QtWidgets>
#include <QString>
#include <dice.h>

class Starter : public QWidget
{
    Q_OBJECT
public:
    explicit Starter(QWidget *parent = 0);
     QLabel * player1, * player2, * message, * error;
     QPushButton * rolldie, * done;
     QGridLayout * hori;
     QVBoxLayout * vert;
     QGroupBox * GP;
     bool rolledit;
     int difficultyS;
     QString user, name;
     dice * scene;
     int winningPlayer;

signals:

public slots:

     void SetUser(QString a, QString b, int S);
     void roll();
     void Back();

};

#endif // STARTER_H

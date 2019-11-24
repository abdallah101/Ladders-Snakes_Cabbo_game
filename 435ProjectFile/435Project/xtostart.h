#ifndef XTOSTART_H
#define XTOSTART_H
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QWidget>
#include <QObject>

/**
  *\file xtostart.h
  */

class xtostart: public QWidget
{
    Q_OBJECT

private:

public:
    explicit xtostart(QWidget *parent = 0);
    QLabel * xtostart_Number, * xtostart_FP;
    QPushButton * xtostart_Stop;
    QGridLayout * xtostart_H;
    QTimer * timer1, * timer2 ;
    bool cont, open;
    int count;

public slots:
    int FirstPlayer();
    void Stop();
    void Close();
};
#endif // XTOSTART_H

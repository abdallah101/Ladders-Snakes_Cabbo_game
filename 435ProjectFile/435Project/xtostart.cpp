#include "xtostart.h"
#include <QFont>
#include <QTimer>
#include <iostream>
using namespace std;
xtostart::xtostart(QWidget *parent) :
    QWidget(parent)
{
    xtostart_FP = new QLabel("");
    xtostart_Number = new QLabel("1");
    QFont font = xtostart_Number->font();
    font.setPointSize(72);
    font.setBold(true);
    xtostart_Number->setFont(font);

    xtostart_Stop = new QPushButton("Stop");
    xtostart_H = new QGridLayout;

    xtostart_H->addWidget(xtostart_FP, 0, 0);
    xtostart_H->addWidget(xtostart_Number, 1, 0);
    xtostart_H->addWidget(xtostart_Stop, 2, 0);

    this->setLayout(xtostart_H);
    this->show();

    count = 1;
    cont = true;
    open = true;
    timer1 = new QTimer();
    timer1->start(100);
    connect(timer1, SIGNAL(timeout()), this, SLOT(FirstPlayer()));
    connect(xtostart_Stop, SIGNAL(clicked()), this, SLOT(Stop()));

    timer2 = new QTimer();
    connect(timer2, SIGNAL(timeout()), this, SLOT(Close()));
}

int xtostart::FirstPlayer()
{
    if(cont)
    {
        count++;
        if (count > 3) count -= 3;
        QString s = "";
        s += (count +'0');
        xtostart_Number->setText(s);
        timer1->start(100);
    }
}

void xtostart::Stop()
{
    QString s = "Player ";
    s += (count + '0');
    s += " will start.";
    xtostart_FP->setText(s);
    cont = false;
    timer2->start(2000);
}

void xtostart::Close()
{
    if (!cont && open) this->close();
    open =false;
}

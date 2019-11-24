#include "xtostart.h"
#include <QFont>
#include <QTimer>
#include <iostream>
using namespace std;
xtostart::xtostart(QWidget *parent) :
    QWidget(parent)
{
    xtostart_Number = new QLabel("1");
    QFont font = xtostart_Number->font();
    font.setPointSize(72);
    font.setBold(true);
    xtostart_Number->setFont(font);

    xtostart_Stop = new QPushButton("Stop");
    xtostart_H = new QGridLayout;

    xtostart_H->addWidget(xtostart_Number, 0, 0);
    xtostart_H->addWidget(xtostart_Stop, 1, 0);

    this->setLayout(xtostart_H);
    this->show();

    count = 1;
    cont = true;
    QTimer * timer1 = new QTimer();
    timer1->start(100);
    connect(timer1, SIGNAL(timeout()), this, SLOT(FirstPlayer()));

    connect(xtostart_Stop, SIGNAL(clicked()), this, SLOT(Stop()));
}

int xtostart::FirstPlayer()
{
    if(cont)
    {
        QString s = "";
        s += (count +'0');
        xtostart_Number->setText(s);
        cout << count << "\n";
        count++;
        if (count > 3) count -= 3;
        timer1->start(100);
    }
}

void xtostart::Stop()
{
    cont = false;
}

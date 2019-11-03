#include "winlose.h"

winlose::winlose(QWidget *parent) :
    QWidget(parent)
{

    win = new QLabel("");
    done = new QPushButton("Exit");
    vert = new QVBoxLayout();

    vert->addWidget(win);
    vert->addWidget(done);
    this->setLayout(vert);

    /**
     * Signal connector to leave game
     */
    QObject::connect(done, SIGNAL(clicked()), this, SLOT(exit()) );

}

void winlose :: setlabel(QString a, int b)
{
    this->user = a;
    if(b == 1)
    {
        win->setText("Player1: YOU WON!");
    }
    else
    {
        win->setText("Player2: YOU WON!");
    }
}

void winlose :: exit ()
{
    this->close();

}

#include "gametwo.h"
#include <QtWidgets>
#include <QWidget>
#include <QApplication>
#include <QTimer>
#include <game2_scene.h>
//#include <game2details.h>
#include <iostream>
#include <mainscreen.h>
gametwo::gametwo(QWidget *parent) :
    QWidget(parent)
{
    start = new QPushButton("Start");
    error = new QLabel("");
    Game2Scene = new game2_scene();
    VB = new QVBoxLayout();
    VB->addWidget(error);
    VB->addWidget(start);
    this->setLayout(VB);
    this->resize(200,200);

    /**
     * removes message after 4 seconds
     */
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    /**
     * starts game 2
     */
    QObject::connect(start, SIGNAL(clicked()), this, SLOT(StartTwo()));


    /**
      * Check for end of game
      */
    timer_end = new QTimer();
    timer_end->start(100);
    connect(timer_end, SIGNAL(timeout()), this, SLOT(check_end()));
}

void gametwo :: setUser (QString a, QString b)
{
    this->name = b;
    this->user = a;
    error->setText("Hello " + this->name + ", Press Start to begin!");
}

void gametwo :: update ()
{
    error->setText("");
}

void gametwo :: StartTwo ()
{
    G2_Info = new game2details();

    Game2Scene->setUser(this->user);
    Game2Scene->Game2_View->setGeometry(G2_Info->x() + 1000, 500, G2_Info->y(), 500);
    Game2Scene->Game2_View->show();

    //st = new xtostart();
    //FirstPlayer = st->count;
    //Game2Scene->turn = FirstPlayer;
    //cout << FirstPlayer << endl;
    this->close();

    open = false;
}

void gametwo :: check_end()
{
    cout << " here \n";
    if (Game2Scene->winner != - 1)
    {
        cout << "inside \n";
        Results();
        //QTimer::singleShot(1000, this, SLOT(Results()));

    }

    if(Game2Scene->deleted == true)
    {
        Game2Scene->deleted = false;
        Game2Scene->Game2_View->close();
        G2_Info->close();
        MainScreen * BacktoMain = new MainScreen();
        BacktoMain->setUser(this->user);
        BacktoMain->show();

        Game2Scene->clear();
        //delete Game2Scene;
    }
}

void gametwo :: Results()
{
    //this->Game2_View->close();

    //this->clear();
    //delete this;
    if (!open)
    {
        res = new g2_results();
        res->setUser(Game2Scene->winner);
        Game2Scene->winner = -1;
        open = false;
    }
    Game2Scene->Game2_View->close();
    G2_Info->close();
    MainScreen * BacktoMain = new MainScreen();
    BacktoMain->setUser(this->user);
    BacktoMain->show();

    Game2Scene->clear();
    delete Game2Scene;



    delete this;
}


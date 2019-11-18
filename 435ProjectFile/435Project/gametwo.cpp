#include "gametwo.h"
#include <QtWidgets>
#include <QWidget>
#include <QApplication>
#include <QTimer>
#include <game2_scene.h>
gametwo::gametwo(QWidget *parent) :
    QWidget(parent)
{
    start = new QPushButton("Start");
    error = new QLabel("");
    //Game2_View = new QGraphicsView();
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
    Game2Scene->setUser(this->user);
    //Game2_View->show();
    Game2Scene->Game2_View->show();
    this->close();

}

#include "gametwo.h"
#include <QtWidgets>
#include <QWidget>
#include <QApplication>
#include <QTimer>

gametwo::gametwo(QWidget *parent) :
    QWidget(parent)
{
    start = new QPushButton("Start");
    error = new QLabel("");
    Game2_View = new QGraphicsView();
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
    this->close();
    Game2_View->setFixedHeight(900);
    Game2_View->setFixedWidth(900);
    Game2_View->setScene(Game2Scene);
    Game2_View->setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    Game2_View->setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    Game2_View->show();
}

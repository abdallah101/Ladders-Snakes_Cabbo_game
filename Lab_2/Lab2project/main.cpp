#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QApplication>
#include<game1scene.h>

int main(int argc, char **argv)
{

QApplication app (argc, argv);

//comment
// :)
//branched

//QGraphicsPixmapItem  * item1 = new QGraphicsPixmapItem();
//QGraphicsPixmapItem  * item2 = new QGraphicsPixmapItem();
//QGraphicsPixmapItem  * item3 = new QGraphicsPixmapItem();
//QGraphicsPixmapItem  * item4 = new QGraphicsPixmapItem();
//QGraphicsScene * scene = new QGraphicsScene();

//item1->setPixmap((QPixmap(":/images/background.jpg")).scaled(900,900));
//scene->addItem(item1);
//item2->setPixmap((QPixmap(":/images/garbage.jpg")).scaled(150,150));
//scene->addItem(item2);
//item3->setPixmap((QPixmap(":/images/garbageman.jpg")).scaled(200,200));
//scene->addItem(item3);
//item4->setPixmap((QPixmap(":/images/rubbish.jpg")).scaled(150,150));
//scene->addItem(item4);

//Creating a scene from custom class game1scene
game1scene *scene1 = new game1scene();

//Setting view
QGraphicsView * view = new QGraphicsView();
view->setScene(scene1);
view->setFixedSize(910,512);
view->setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
view->setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
view->show();

return app.exec();
}

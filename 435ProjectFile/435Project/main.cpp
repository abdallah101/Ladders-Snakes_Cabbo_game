#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QApplication>
#include <user.h>
#include <mainmenu_widget.h>
#include <QWidget>
#include <QtWidgets>
int main(int argc, char **argv)
{

QApplication app (argc, argv);

MainMenu_Widget widget;

widget.show();



return app.exec();
}

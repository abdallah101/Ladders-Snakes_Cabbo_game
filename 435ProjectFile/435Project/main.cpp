#include <registermenu.h>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QApplication>
#include <user.h>
#include <mainmenu_widget.h>
#include <QWidget>
#include <QtWidgets>
#include <registermenu.h>

int main(int argc, char **argv)
{

QApplication app (argc, argv);

//initialization
MainMenu_Widget widget;
widget.show();


return app.exec();
}

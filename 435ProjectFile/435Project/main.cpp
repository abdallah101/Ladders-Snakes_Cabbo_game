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
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char **argv)
{

// hello check

QApplication app (argc, argv);

//initialization
MainMenu_Widget widget;
widget.show();


return app.exec();
}

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

/**
  * \mainpage Project
  */

int main(int argc, char **argv)
{

    QApplication app (argc, argv);

    /**
     * @brief Initialization
     */

    MainMenu_Widget widget;
    widget.show();

    return app.exec();
}

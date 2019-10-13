#include "mainscreen.h"
#include <QApplication>
#include <mainmenu_widget.h>
#include <QString>

/**
  *\file mainscreen.cpp
  */

MainScreen::MainScreen(QWidget *parent) :
    QWidget(parent)
{

    GameOne = new QPushButton("Game One");
    GameTwo = new QPushButton("Game Two");
    UsernameL = new QLabel(this->user);
    //UsernameL->setFixedSize(50,50);
    Settings = new QPushButton("Settings");
    ChooseL = new QLabel("Pick a Game to Start");
    pic = new QLabel("profile pic here");
    History = new QPushButton("History");
    pic->setFixedSize(150,150);
    vert = new QVBoxLayout();
    horiz = new QGridLayout();

    //Setting displayed username font
    QFont font = UsernameL->font();
    font.setPointSize(16);
    font.setBold(true);
    UsernameL->setFont(font);



    horiz->addWidget(UsernameL,0,3);
    horiz->addWidget(pic,0,0);
    horiz->setColumnMinimumWidth(2,50);
    vert->addItem(horiz);
    vert->addWidget(ChooseL,1,0);
    vert->addWidget(GameOne,2,0);
    vert->addWidget(GameTwo,3,0);
    vert->addWidget(History,4,0);
    vert->addWidget(Settings,5,0);


     this->setLayout(vert);

}

void MainScreen :: GotoTwo ()
{

}

void MainScreen :: GotoOne ()
{

}

void MainScreen :: GotoSettings()
{

}
/**
 * \brief Function which opens a window with user name and profile picture.
 * \param Takes no parameter
 * \return nothing (type: void)
 */

void MainScreen :: setUser(QString u)
{
    this->user = u;

    QFile file("UserData.txt");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QRegExp rx("(\\ |\\,|\\.|\\:|\\t)"); //RegEx for ' ' or ',' or '.' or ':' or '\t'
    QTextStream lite(&file);
    QString sp;
    QStringList query;


    while(!lite.atEnd())
    {

        sp = lite.readLine();
        query = sp.split(rx);

        if(user == query[4]) break;

    }
    file.close();


    UsernameL->setText(query[0] + " " +query[1]);
    QImage green;
    green.load(QDir::currentPath() + "/UserProfilePics/"+u+".jpg");

    pic->setScaledContents(true);
    green.scaledToWidth(pic->width(), Qt::SmoothTransformation);
    //green.scaledToHeight(pic->height(), Qt::SmoothTransformation);


    pic->setPixmap(QPixmap::fromImage(green));
}

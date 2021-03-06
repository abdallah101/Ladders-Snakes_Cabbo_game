#include "mainscreen.h"
#include <QApplication>
#include <mainmenu_widget.h>
#include <QString>
#include <settings.h>
#include <gameone.h>
#include <game1_scene.h>
#include <historywidget.h>

/**
  *\file mainscreen.cpp
  */

MainScreen::MainScreen(QWidget *parent) :
    QWidget(parent)
{

    /**
     * Setting up the widget items
     */
    GameOneB = new QPushButton("Game One");
    GameTwo = new QPushButton("Game Two");
    UsernameL = new QLabel(this->user);
    SettingsB = new QPushButton("Settings");
    ChooseL = new QLabel("Pick a Game to Start");
    pic = new QLabel("profile pic here");
    History = new QPushButton("History");
    pic->setFixedSize(150,150);
    vert = new QVBoxLayout();
    horiz = new QGridLayout();
    SignOut = new QPushButton("Sign Out");
    //SettingsB->setEnabled(false);
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
    vert->addWidget(GameOneB,2,0);
    vert->addWidget(GameTwo,3,0);
    vert->addWidget(History,4,0);
    vert->addWidget(SettingsB,5,0);
    vert->addWidget(SignOut, 6, 0);


     this->setLayout(vert);


    /**
     * Signal connector to mainmenu
     */
    QObject::connect(SignOut, SIGNAL(clicked()), this, SLOT(goBack()) );


    /**
     * Signal connector to settings
     */
    QObject::connect(SettingsB, SIGNAL(clicked()), this, SLOT(GotoSettings()) );

    /**
     * Signal connector to Game 1
     */
    QObject::connect(GameOneB, SIGNAL(clicked()), this, SLOT(GotoOne()) );

    /**
     * Signal connector to Game 1
     */
    QObject::connect(GameTwo, SIGNAL(clicked()), this, SLOT(GotoTwo()) );

    /**
     * Signal connector to history of player
     */
    QObject::connect(History, SIGNAL(clicked()), this, SLOT(history()) );


}


/**
 * \brief Function to go to game two
 * \param Takes no parameter
 * \return nothing (type: void)
 */

void MainScreen :: GotoTwo ()
{
    this->close();
    game2partner = new gametwo();
    game2partner->setUser(this->user,this->name);
    game2partner->show();
}

/**
 * \brief Function to go to game one main menu to choose diffculty
 * \param Takes no parameter
 * \return nothing (type: void)
 */

void MainScreen :: GotoOne ()
{
    //Creating a scene from custom class game1scene
    this->close();
    GameOne * scene1 = new GameOne();
    scene1->SetUser(this->user, this->name);
    scene1->show();

}

/**
 * \brief Opens settings widget for user to change profile pic or password
 * \param Takes no parameter
 * \return nothing (type: void)
 */

void MainScreen :: GotoSettings()
{

    partner1.SearchUser(this->user);
    this->close();
    partner1.show();
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



    UsernameL->setText(query[0] + " " +query[1]);
    name = query[0] + " " + query[1];
    QImage green;
    if (green.load(QDir::currentPath() + "/UserProfilePics/"+u+".jpg"))
    {
        pic->setScaledContents(true);
        green.scaledToWidth(pic->width(), Qt::SmoothTransformation);
    }


    else if (green.load(QDir::currentPath() + "/UserProfilePics/"+u+".jpeg"))
    {
        pic->setScaledContents(true);
        green.scaledToWidth(pic->width(), Qt::SmoothTransformation);
    }

    pic->setPixmap(QPixmap::fromImage(green));

    //int day = QDate::currentDate().day();

    if(query[6].toInt() ==  QDate::currentDate().month() && query[7].toInt() ==  QDate::currentDate().day())
    {
        UsernameL->setText(query[0] + " " + query [1] + "\n"  + "HAPPY BIRTHDAY!!");
    }

    file.close();


}
void MainScreen :: goBack()
{
    MainMenu_Widget * partner;
    partner = new MainMenu_Widget();
    this->close();
    partner->show();

}

void MainScreen :: history()
{
    HistoryWidget * partner = new HistoryWidget();
    partner->setUser(this->user);
    this->close();
    partner->show();
}

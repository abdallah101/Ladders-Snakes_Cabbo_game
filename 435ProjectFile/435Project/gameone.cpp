#include "gameone.h"
#include <QApplication>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QWidget>
#include <QTimer>
#include <QFile>
#include <QPixmap>
#include <QImage>
#include <QDir>
#include <dice.h>
#include <custWid.h>
#include <game1_modes.h>
#include <starter.h>
GameOne::GameOne(QWidget *parent) :
    QWidget(parent)

{
    startButton = new QPushButton ("New Game");
    SetLaddersSnakes = new QPushButton ("Customize the positions of snakes and ladders.");
    easy = new QRadioButton("easy");
    medium = new QRadioButton("medium");
    hard = new QRadioButton("hard");
    twoplayers = new QRadioButton("2 players");
    choose = new QLabel("Choose difficulty");
    VerticalRadioB = new QVBoxLayout();
    GP = new QGroupBox();
    error = new QLabel("");
    resume = new QPushButton("Resume previous game");

    VerticalRadioB->addWidget(easy);
    VerticalRadioB->addWidget(medium);
    VerticalRadioB->addWidget(hard);
    VerticalRadioB->addWidget(twoplayers);
    GP->setLayout(VerticalRadioB);


    Horiz = new QGridLayout();
    Horiz->addWidget(startButton,0,0);
    Horiz->addWidget(GP,1,0);
    Horiz->addWidget(SetLaddersSnakes,2,0);
    Horiz->addWidget(error,3,0);
    Horiz->addWidget(resume,4,0);
    this->setLayout(Horiz);
    this->resize(200, 200);
    QObject::connect(startButton, SIGNAL(clicked()), this, SLOT(start()));
    QObject::connect(SetLaddersSnakes, SIGNAL(clicked()), this, SLOT(customize()));
    QObject::connect(resume, SIGNAL(clicked()), this, SLOT(resumegame()));

    /**
     * removes message after 4 seconds
     */
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

}

void GameOne :: start()
{

    if(!easy->isChecked() && !medium->isChecked() && !hard->isChecked() && !twoplayers->isChecked())
    {
        error->setText("Choose difficulty first!");
        timer->start(4000);
    }
    else if(easy->isChecked())
    {
        this->close();
        scene = new Starter();

        scene->SetUser(this->user, this->name, 1);
        scene->show();
    }
    else if (medium->isChecked())
    {
        this->close();
        scene = new Starter();

        scene->SetUser(this->user, this->name, 2);
        scene->show();
    }
    else if (hard->isChecked())
    {
        this->close();
        scene = new Starter();

        scene->SetUser(this->user, this->name, 3);
        scene->show();
    }
    else if (twoplayers->isChecked())
    {
        this->close();
        scene = new Starter();

        scene->SetUser(this->user, this->name, 4);
        scene->show();
    }



}

void GameOne :: customize()
{
    this->close();
    scene1 = new custWid();
    scene1->SetUser(this->user);
    scene1->show();
}

void GameOne :: SetUser (QString d, QString n)
{
    this->user = d;
    this->name = n;
}

void GameOne :: update ()
{
    error->setText("");
}

void GameOne :: resumegame()
{

    QFile file(QDir::currentPath() + "/history.txt");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QRegExp rx("(\\,)"); //RegEx for ','
    QTextStream lite(&file);
    QString sp;
    QStringList query;

    QString temp = ""; //this will copy all the history of the user to add to it then copy it back

    int p, d;
    while(!lite.atEnd())
    {

        sp = lite.readLine();
        query = sp.split(rx);

        if(this->user == query[0])
        {
            break;
        }

    }

    file.close();


    if(query[query.size()-2] != "x")
    {
        error->setText("No previous Game has been found\nCreate new Game");
    }
    else
    {

        this->close();
        scene2 = new dice();

        for(int i =query.size()-3;i != 0; i--)
        {
            if(query[i] == "x" || query[i] == "l" || query[i] == "w")
            {
                p = query[i+1].toInt();
                d = query[i+2].toInt();
            }
        }

        scene2->SetUser(this->user, this->name, d, p, true);
        scene2->show();
    }
}

#include "gametwo.h"
#include <QtWidgets>
#include <QWidget>
#include <QApplication>
#include <QTimer>
#include <game2_scene.h>
#include <iostream>
#include <mainscreen.h>
#include <cards.h>


gametwo::gametwo(QWidget *parent) :
    QWidget(parent)
{
    start = new QPushButton("Start");
    error = new QLabel("");
    resume = new QPushButton("Resume");
    Game2Scene = new game2_scene();
    VB = new QVBoxLayout();
    VB->addWidget(error);
    VB->addWidget(start);
    VB->addWidget(resume);
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

    /**
     * resumes old game
     */
    QObject::connect(resume, SIGNAL(clicked()), this, SLOT(ResumeGame()));


    /**
      * Check for end of game
      */
    timer_end = new QTimer();
    timer_end->start(1000);
    connect(timer_end, SIGNAL(timeout()), this, SLOT(check_end()));
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
    G2_Info = new game2details();

    Game2Scene->setUser(this->user);
    Game2Scene->Game2_View->setGeometry(G2_Info->x() + 1000, 500, G2_Info->y(), 500);
    Game2Scene->Game2_View->show();

    //st = new xtostart();
    //FirstPlayer = st->count;
    //Game2Scene->turn = FirstPlayer;
    //cout << FirstPlayer << endl;
    this->close();

    open = false;
}

void gametwo :: check_end()
{
    cout << " here \n";
    if (Game2Scene->winner != - 1)
    {
        cout << "inside \n";
        QTimer::singleShot(5000, this, SLOT(Results()));
        Game2Scene->winner = - 1;
    }

    if(Game2Scene->deleted == true)
    {

        Game2Scene->deleted = false;

        QFile data(QDir::currentPath() + "/history2.txt");
            data.open(QIODevice::Text | QIODevice::ReadOnly);
            QString dataText = data.readAll();
            data.close();


        QFile file(QDir::currentPath() + "/history2.txt");
        file.open(QIODevice::ReadOnly|QIODevice::Text);
        QRegExp rx("(\\,)"); //RegEx for ','
        QTextStream lite(&file);
        QString sp;
        QStringList query;

        QString temp = ""; //this will copy all the history of the user to add to it then copy it back

        while(!lite.atEnd())
        {

            sp = lite.readLine();
            query = sp.split(rx);

            if(this->user == query[0])
            {
                break;
            }

        }



        for(int i = 0 ; i < query.size()-1 ; i++)
        {
            temp = temp  + query[i] + ",";
        }
        QRegularExpression re(temp);


        if(query[1] == "-3")
        {
            temp = user + "," ;
            for(int i = 0 ; i < 3; i++)
            {
                for(int j = 0 ; j < 4 ; j++)
                {
                    temp = temp + QString::number(this->Game2Scene->c[i][j].first) + "," + QString::number(this->Game2Scene->c[i][j].second) + "," ;
                }
            }

        }
        else
        {
            for(int i = 0 ; i < 3; i++)
            {
                for(int j = 0 ; j < 4 ; j++)
                {
                    temp = temp + QString::number(this->Game2Scene->c[i][j].first) + "," + QString::number(this->Game2Scene->c[i][j].second) + "," ;
                }
            }

        }

        int count = 0;
        while(!this->Game2Scene->pile.empty())
        {
            pair<int, int>  pile1 = this->Game2Scene->pile.top();
            count += 2;
            temp = temp + QString::number(pile1.first) + "," + QString::number(pile1.second) + ",";
            this->Game2Scene->pile.pop();
        }

         temp = temp + QString::number(count) + ",";

         pair<int, int>  pile1;

         if(!Game2Scene->drawn.empty()) pile1= this->Game2Scene->drawn.top();
         else pile1 = {-1,-1};

        temp = temp + QString::number(pile1.first) + "," + QString::number(pile1.second) + ",";
        temp = temp + "x,";

        //temp = user + ",-1," + QString::number(difficulty) + "," + QString::number(player->cell + steps) + ",";
        dataText.replace(re, temp);


        QFile newData(QDir::currentPath() + "/history2.txt");
        data.resize(0);
        if(newData.open(QFile::WriteOnly | QFile::Truncate))
        {
            QTextStream out(&newData);
            out << dataText;
        }
        newData.close();
        file.close();






        //Game2Scene->deleted = false;
        Game2Scene->Game2_View->close();
        G2_Info->close();
        MainScreen * BacktoMain = new MainScreen();
        BacktoMain->setUser(this->user);
        BacktoMain->show();

        Game2Scene->clear();
        //delete Game2Scene;
    }
}

void gametwo :: Results()
{

    QFile data(QDir::currentPath() + "/history2.txt");
    data.open(QIODevice::Text | QIODevice::ReadOnly);
    QString dataText = data.readAll();
    data.close();


    QFile file(QDir::currentPath() + "/history2.txt");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QRegExp rx("(\\,)"); //RegEx for ','
    QTextStream lite(&file);
    QString sp;
    QStringList query;

    QString temp = ""; //this will copy all the history of the user to add to it then copy it back

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

    for(int i = 0 ; i < query.size()-1 ; i++)
    {
        temp = temp  + query[i] + ",";
    }

    QRegularExpression re(temp);
    /**
      * new user
      */

    if(query[1] == "-3")
    {
        temp = user + "," ;
        for(int i = 0 ; i < 3; i++)
        {
            for(int j = 0 ; j < 4 ; j++)
            {
                temp = temp + QString::number(this->Game2Scene->c[i][j].first) + "," + QString::number(this->Game2Scene->c[i][j].second) + "," ;
            }
        }

        //temp = temp + "f,";
    }
    else
    {
        for(int i = 0 ; i < 3; i++)
        {
            for(int j = 0 ; j < 4 ; j++)
            {
                temp = temp + QString::number(this->Game2Scene->c[i][j].first) + "," + QString::number(this->Game2Scene->c[i][j].second) + "," ;
            }
        }
        //temp = temp + "f,";
    }

    int count = 0 ;
    while(!this->Game2Scene->pile.empty())
    {
        pair<int, int>  pile1 = this->Game2Scene->pile.top();
        count += 2;
        temp = temp + QString::number(pile1.first) + "," + QString::number(pile1.second) + ",";
        this->Game2Scene->pile.pop();
    }

    temp = temp + QString::number(count) + ",";

    pair<int, int>  pile1;
    if(!Game2Scene->drawn.empty()) pile1= this->Game2Scene->drawn.top();
    else pile1 = {-1,-1};

    temp = temp + QString::number(pile1.first) + "," + QString::number(pile1.second) + ",";
    temp = temp + "f,";


    //temp = user + ",-1," + QString::number(difficulty) + "," + QString::number(player->cell + steps) + ",";
    dataText.replace(re, temp);


    QFile newData(QDir::currentPath() + "/history2.txt");
    data.resize(0);
    if(newData.open(QFile::WriteOnly | QFile::Truncate))
    {
        QTextStream out(&newData);
        out << dataText;
    }
    newData.close();

    if (!open)
    {
        res = new g2_results();
        res->setUser(Game2Scene->s[0] + 4, Game2Scene->s[1] + 4, Game2Scene->s[2] + 4);
        open = false;
    }
    Game2Scene->Game2_View->close();
    G2_Info->close();
    MainScreen * BacktoMain = new MainScreen();
    BacktoMain->setUser(this->user);
    BacktoMain->show();

    Game2Scene->clear();
    delete Game2Scene;



    delete this;
}


void gametwo:: ResumeGame()
{

    QFile file(QDir::currentPath() + "/history2.txt");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QRegExp rx("(\\,)"); //RegEx for ','
    QTextStream lite(&file);
    QString sp;
    QStringList query;


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


    QTextStream out(stdout);
    out << "Before: " << query[query.size()-2] << endl;

    if(query[query.size()-2] != "x")
    {
        error->setText("No previous Game has been found\nCreate new Game");
    }
    else
    {

        this->close();

        G2_Info = new game2details();

        Game2Scene->setUser(this->user);
        Game2Scene->Game2_View->setGeometry(G2_Info->x() + 1000, 500, G2_Info->y(), 500);
        Game2Scene->Game2_View->show();
        Game2Scene->FirstTurn = false;


        //st = new xtostart();
        //FirstPlayer = st->count;
        //Game2Scene->turn = FirstPlayer;
        //cout << FirstPlayer << endl;
        this->close();

        open = false;

        Game2Scene->nbofFlips = 2;
        Game2Scene->FirstTurn = false;

        while (!Game2Scene->pile.empty()) Game2Scene->pile.pop();
        while (!Game2Scene->drawn.empty()) Game2Scene->drawn.pop();

        pair<int,int> e;
        e.first = query[query.size() - 4].toInt();
        e.second = query[query.size()-3].toInt();

        if (e.first != -1) Game2Scene->drawn.push(e);

        out << "Size: "  << Game2Scene->pile.size() <<  endl;

        int count = 0 ;
        int j = 3;
        int k = 2;
        for(int i = query.size()-6; i > 0; i--)
        {
            if(count < query[query.size() - 5].toInt())
            {

                e.second = query[i].toInt();
                count += 2;
                i--;
                e.first = query[i].toInt();
                Game2Scene->pile.push(e);
                //out << "SS: " << e.first << "  " << e.second << endl;
            }
            else if(query[i] == "x" || query[i] == "f" || query[i] == this->user)
            {
                break;
            }
            else
            {
                if(j == -1)
                {
                    j = 3;
                    k--;
                }


                Game2Scene->c[k][j].second = query[i].toInt();
                i--;
                Game2Scene->c[k][j].first = query[i].toInt();
                j--;
            }
        }

        out << "Size: "  << Game2Scene->pile.size() <<  endl;
        e = Game2Scene->pile.top();
        Game2Scene->fromPile->number = e.first + e.second * 13 + 1;

        if (!Game2Scene->drawn.empty())
        {
            Game2Scene->toPile->number = Game2Scene->drawn.top().first + Game2Scene->drawn.top().second * 13 + 1;
            Game2Scene->toPile->setPixmap((QPixmap(QDir::currentPath() + "/Images/" + QString::number(Game2Scene->toPile->number) + ".png")).scaled(80,100));
        }

        for(int i = 0 ; i < 12; i ++)
        {
            Game2Scene->playerCards[i]->number = Game2Scene->c[i/4][i%4].first + Game2Scene->c[i/4][i%4].second * 13 + 1;
        }

    }


}


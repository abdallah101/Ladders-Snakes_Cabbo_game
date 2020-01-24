#include "historywidget.h"
#include <QApplication>
#include <QtWidgets>
#include <mainscreen.h>
#include <QFile>
#include <QTextStream>


HistoryWidget::HistoryWidget(QWidget *parent) :
    QWidget(parent)
{
    back = new QPushButton("Back");
    VB = new QVBoxLayout();
    game1 = new QLabel("None");
    game2 = new QLabel("None");
    p0 = new QProgressBar();
    p1 = new QProgressBar();
    p2 = new QProgressBar();
    p3 = new QProgressBar();
    p4 = new QProgressBar();
    p5 = new QProgressBar();
    p6 = new QProgressBar();
    VB->addWidget(game1);
    GP = new QGridLayout();



    GP->addWidget(p0,0,1);
    GP->addWidget(p1,1,1);
    GP->addWidget(p2,2,1);
    GP->addWidget(p3,3,1);
    GP->addWidget(p4,4,1);
    GP->addWidget(p5,5,1);
    GP->addWidget(p6,6,1);



    llb0 = new QLabel("0:");

    llb1 = new QLabel("1:");

    llb2 = new QLabel("2:");

    llb3 = new QLabel("3:");

    llb4 = new QLabel("4:");

    llb5 = new QLabel("5:");

    llb6 = new QLabel("6:");

    GP->addWidget(llb0,0,0);
    GP->addWidget(llb1,1,0);
    GP->addWidget(llb2,2,0);
    GP->addWidget(llb3,3,0);
    GP->addWidget(llb4,4,0);
    GP->addWidget(llb5,5,0);
    GP->addWidget(llb6,6,0);

    VB->addItem(GP);
    VB->addWidget(game2);
    VB->addWidget(back);

    this->setLayout(VB);

    /**
     * Signal connector to history of player
     */
    QObject::connect(back, SIGNAL(clicked()), this, SLOT(BACK()) );

}


void HistoryWidget :: setUser(QString a)
{
    this->user = a;

    QFile file(QDir::currentPath() + "/history.txt");
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


    vector <double> temp;
    int w = 0;
    int l = 0;
    int x = 0;
    double dieRolls[7] = {0,0,0,0,0,0,0};
    for(int i = 0 ; i < query.size()-1 ; i++)
    {
        if(query[i] == "x")
        {
            x++;
        }
        else if (query[i] == "l" )
        {
            l++;
        }
        else if (query[i] == "w")
        {
            w++;
        }
        else if (query[i] == this->user)
        {}
        else if (query[i] < 0)
        {}
        else
        {
            temp.push_back(query[i].toDouble());
        }
    }
    x = x - w - l;


    for(int i = 0 ; i < temp.size()-2; i+= 2)
    {
        int z = temp[i+2] - temp[i];
        if(z < 7 && z >-1)
        {
            dieRolls[z]++;

        }


    }

    double max = 0;
    for(int i = 0 ; i < 7 ; i++)
    {
        max = max + dieRolls[i];
    }

    //game1->setText(QString::number(dieRolls[0]) + "\n" + QString::number(dieRolls[1]) + "\n" + QString::number(dieRolls[2]) + "\n" + QString::number(dieRolls[3]) + "\n" + QString::number(dieRolls[4]) + "\n" +
      //      QString::number(dieRolls[5]) + "\n" + QString::number(dieRolls[6]) + "\n");

    for(int i = 0; i < 7; i++)
    {
        dieRolls[i] = (dieRolls[i]/max)*100.0;
    }

    game1->setText("You have won/lost/left: " + QString::number(w) +"/"+ QString::number(l) + "/" + QString::number(x) + "\n" + "The following are YOUR probability of getting the die Rolls \n0,1,2,3,4,5,6 respectively");
    p0->setValue(dieRolls[0]);
    p1->setValue(dieRolls[1]);
    p2->setValue(dieRolls[2]);
    p3->setValue(dieRolls[3]);
    p4->setValue(dieRolls[4]);
    p5->setValue(dieRolls[5]);
    p6->setValue(dieRolls[6]);


    QFile file1(QDir::currentPath() + "/history2.txt");
    file1.open(QIODevice::ReadOnly|QIODevice::Text);
    //rx("(\\,)"); //RegEx for ','
    QTextStream lite1(&file1);



    while(!lite1.atEnd())
    {

        sp = lite1.readLine();
        query = sp.split(rx);

        if(this->user == query[0])
        {
            break;
        }

    }

    file1.close();


    int count = 0 ;
    int j = 3;
    int k = 2;
    int sum[3] = {0,0,0};

    for(int i = query.size()-6; i > 0; i--)
    {
        if(count < query[query.size() - 5].toInt())
        {


            count++;

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



            i--;
            sum[k] = sum[k] + query[i].toInt();
            j--;
        }
    }


    game2->setText("Previous Game's Score: \nPlayer 1: " + QString::number(sum[0]) + "\nPlayer 2: " + QString::number(sum[1]) +"\nPlayer 3: " + QString::number(sum[2]));


}

void HistoryWidget :: BACK()
{
    MainScreen * partner = new MainScreen();
    partner->setUser(this->user);
    this->close();
    partner->show();
}

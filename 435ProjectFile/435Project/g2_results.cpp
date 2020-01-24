#include "g2_results.h"
#include <QGraphicsTextItem>
#include <set>
#include <QFont>
#include <QMediaPlayer>

g2_results::g2_results()
{

    g2_resultsView = new QGraphicsView();
    g2_resultsView->setFixedHeight(418);
    g2_resultsView->setFixedWidth(744);
    g2_resultsView->setScene(this);
    g2_resultsView->setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    g2_resultsView->setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));

    text = new QGraphicsTextItem();
    //text->setFont(serifFont);
    text->setDefaultTextColor("#D4AF37");

        text->setPos(100, 100);
        this->addItem(text);
    /**
     * Setting the background
     */

    QImage green;
    this->setSceneRect(0,0,744,418);
    if (green.load(QDir::currentPath() + "/Images/res.jpg"))
    {
        this->setBackgroundBrush(QBrush(green.scaledToHeight(418).scaledToWidth(744)));
    }
    g2_resultsView->show();

    QMediaPlayer * player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile(QDir::currentPath() + "/Sounds/victory.mp3"));
    player->setVolume(50);
    player->play();

}

void g2_results :: setUser (int a, int b, int c)
{
    if (a < b && a < c) winner= 1;
    else if (b < a && b < c) winner = 2;
    else if (c < b && c < a) winner = 3;
    else if (a > b && a > c) winner = 4;  // tie 2-3
    else if (b > a && b > c) winner = 5;  // tie 1-3
    else if (c > b && c > a) winner = 6;  // tie 2-1
    else winner = 7; //all tie


    QString str = "Payer1: " + QString::number(a) + "\n" + "Payer2: " + QString::number(b) + "\n" + "Payer3: " + QString::number(c) + "\n";

    if(winner == 1)
    {
       str = str + "Player 1 won!";
    }
    else if (winner == 2)
    {
         str = str +"Player 2 won!";
    }
    else if (winner == 3)
    {
       str = str + "Player 3 won!";
    }
    else if (winner == 4)
    {
         str = str + "Players 2 and 3 tied!";
    }
    else if (winner == 5)
    {
         str = str + "Players 1 and 3 tied!";
    }
    else if (winner == 6)
    {
         str = str + "Players 2 and 1 tied!";
    }
    else if (winner == 7)
    {
        str = str + "What are the Odds! EVERYONE TIED";
    }
    text->setPlainText(str);
}

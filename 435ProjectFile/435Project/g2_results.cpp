#include "g2_results.h"
#include <QGraphicsTextItem>
#include <set>
#include <QFont>

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

        text->setPos(230, 220);
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

}

void g2_results :: setUser (int win)
{
    this->winner = win;
    if(winner == 1)
    {
       text->setPlainText("Player 1 won!");
    }
    else if (winner == 2)
    {
                    text->setPlainText("Player 2 won!");
    }
    else if (winner == 3)
    {
        text->setPlainText("Player 3 won!");
    }
    else if (winner == 4)
    {
        text->setPlainText("Players 2 and 3 tied!");
    }
    else if (winner == 5)
    {
        text->setPlainText("Players 1 and 3 tied!");
    }
    else if (winner == 6)
    {
        text->setPlainText("Players 2 and 1 tied!");
    }
    else
    {
        text->setPlainText("What are the Odds! EEVERYONE TIED");
    }

}

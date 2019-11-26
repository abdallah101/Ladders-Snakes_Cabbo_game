#include "g2_results.h"

g2_results::g2_results()
{

    g2_resultsView = new QGraphicsView();
    g2_resultsView->setFixedHeight(400);
    g2_resultsView->setFixedWidth(400);
    g2_resultsView->setScene(this);
    g2_resultsView->setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    g2_resultsView->setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));


    /**
     * Setting the background
     */

    QImage green;
    this->setSceneRect(0,0,400,400);
    if (green.load(QDir::currentPath() + "/Images/res.jpg"))
    {
        this->setBackgroundBrush(QBrush(green.scaledToHeight(900).scaledToWidth(900)));
    }
    g2_resultsView->show();

}

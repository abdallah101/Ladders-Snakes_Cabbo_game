#ifndef G2_RESULTS_H
#define G2_RESULTS_H
#include <QGraphicsView>
#include <QDir>
class g2_results : public QGraphicsScene
{
     Q_OBJECT
public:
    g2_results();
    QGraphicsView * g2_resultsView;
    int winner;
    QGraphicsTextItem * text;
    void setUser(int win);
};

#endif // G2_RESULTS_H

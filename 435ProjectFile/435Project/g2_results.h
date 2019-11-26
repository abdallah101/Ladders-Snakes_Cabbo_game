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
};

#endif // G2_RESULTS_H

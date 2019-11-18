#ifndef VIEWGAMETWO_H
#define VIEWGAMETWO_H

#include <QGraphicsView>
#include <QString>

class ViewGameTwo : public QGraphicsView
{
private:
    //void closeEvent(QCloseEvent *bar);
public:
    ViewGameTwo();
    QString user;

public slots:
    void setUser(QString a);

};

#endif // VIEWGAMETWO_H

#ifndef GAMETWO_H
#define GAMETWO_H

#include <QtWidgets>
#include <QWidget>
#include <QApplication>
#include <QString>
#include <QTimer>
#include <QGraphicsView>
#include <game2_scene.h>
#include <game2details.h>
#include <xtostart.h>
#include <g2_results.h>
class gametwo : public QWidget
{
    Q_OBJECT
public:
    explicit gametwo(QWidget *parent = 0);
    QPushButton * start;
    QLabel * error;
    QString user, name;
    QVBoxLayout * VB;
    QTimer * timer, * timer_end;
    game2_scene * Game2Scene;
    QWidget * G2_Info;
    xtostart * st;
    int FirstPlayer;
    g2_results * res;
    bool open;


signals:

public slots:

    void setUser(QString a, QString b);
    void update();
    void StartTwo();
    void check_end();
    void Results();

};

#endif // GAMETWO_H

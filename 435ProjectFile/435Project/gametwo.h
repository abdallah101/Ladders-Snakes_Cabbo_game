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

class gametwo : public QWidget
{
    Q_OBJECT
public:
    explicit gametwo(QWidget *parent = 0);
    QPushButton * start;
    QLabel * error;
    QString user, name;
    QVBoxLayout * VB;
    QTimer * timer;
    game2_scene * Game2Scene;
    QWidget * G2_Info;
    xtostart * st;
    int FirstPlayer;


signals:

public slots:

    void setUser(QString a, QString b);
    void update();
    void StartTwo();


};

#endif // GAMETWO_H

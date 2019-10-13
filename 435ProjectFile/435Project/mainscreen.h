#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QtWidgets>
#include <QObject>
#include <QString>


/**
  *\file mainscreen.h
  */

class MainScreen : public QWidget
{
    Q_OBJECT
public:
    explicit MainScreen(QWidget *parent = 0);

    QPushButton * GameOne, * GameTwo, * History, * Settings;
    QLabel * ChooseL, * UsernameL, * pic;


    QVBoxLayout * vert;
    QGridLayout * horiz;

    QString user;


signals:

public slots:

    void GotoTwo ();

    void GotoOne ();

    void GotoSettings();

    void setUser(QString u);

};

#endif // MAINSCREEN_H

#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QtWidgets>
#include <QObject>
#include <QString>
#include <settings.h>
#include <gametwo.h>
#include <game2details.h>

/**
  *\file mainscreen.h
  */

class MainScreen : public QWidget
{
    Q_OBJECT
public:
    explicit MainScreen(QWidget *parent = 0);

    QPushButton * GameOneB, * GameTwo, * History, * SettingsB, * SignOut;
    QLabel * ChooseL, * UsernameL, * pic;
    gametwo * game2partner;


    QVBoxLayout * vert;
    QGridLayout * horiz;

    Settings partner1;
    QString user, name;




signals:

public slots:

    void GotoTwo ();

    void GotoOne ();

    void GotoSettings();

    void setUser(QString u);

    void goBack();

};

#endif // MAINSCREEN_H

#ifndef MAINMENU_WIDGET_H
#define MAINMENU_WIDGET_H

#include <QWidget>
#include <QObject>
#include <QtWidgets>
#include <strings.h>
#include <mainscreen.h>

/**
  *\file mainmenu_widget.h
  */


class MainMenu_Widget : public QWidget
{
    Q_OBJECT
public:
    explicit MainMenu_Widget(QWidget *parent = 0);
    QPushButton * Login_Button, * Register_Button, * LoginGuest_Button;
    QLineEdit * Username, * Password;
    QVBoxLayout * VerticalL;
    QGridLayout * Horizantel;
    QGroupBox * GroupBox;
    QLabel * UsernameL, *PasswordL, *error;
    QWidget * partner1;

    MainScreen * partner2;

signals:

public slots:

    void Open_GameSelection();
    //void NewUser (string username, string FirstName, string LastName, String Age, String );
    void OpenRegisterMenu();
    void keyPressEvent (QKeyEvent * event);
    void update();

};

#endif // MAINMENU_WIDGET_H

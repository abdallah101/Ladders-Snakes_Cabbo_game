#ifndef MAINMENU_WIDGET_H
#define MAINMENU_WIDGET_H

#include <QWidget>
#include <QObject>
#include <QtWidgets>
#include <strings.h>


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
    QLabel * UsernameL, *PasswordL;
    QWidget * partner1;


signals:

public slots:

    void Open_GameSelection();
    //void NewUser (string username, string FirstName, string LastName, String Age, String );
    void OpenRegisterMenu();

};

#endif // MAINMENU_WIDGET_H

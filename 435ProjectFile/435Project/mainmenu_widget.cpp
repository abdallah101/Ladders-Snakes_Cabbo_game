#include "mainmenu_widget.h"
#include <QApplication>
#include <QWidget>
#include <QtWidgets>
#include <strings.h>
#include <QLabel>
#include <QLayout>
#include <registermenu.h>
#include <QFile>
#include <QTextStream>
#include <mainscreen.h>

/**
  *\file mainmenu_widget.cpp
  */

MainMenu_Widget::MainMenu_Widget(QWidget *parent) :
    QWidget(parent)
{
    /**
     * Creating buttons, input boxes, and Labels
     */

    Login_Button = new QPushButton("Login");
    Register_Button = new QPushButton("Register");
    LoginGuest_Button = new QPushButton("Login as Guest");
    Username = new QLineEdit();
    Password = new QLineEdit();
    Password->setEchoMode(QLineEdit::Password);
    UsernameL = new QLabel("Username: ");
    PasswordL = new QLabel("Password: ");
    error = new QLabel("");

    /**
     * Creating layouts
     */

    VerticalL = new QVBoxLayout();
    Horizantel = new QGridLayout();


    /**
     * Adding widgets to horizantel layout
    */

    Horizantel->addWidget(Username,1,0);
    Horizantel->addWidget(Password,1,2);
    Horizantel->addWidget(UsernameL,0,0);
    Horizantel->addWidget(PasswordL,0,2);


    /**
     * Adding widgets to vertical layout
     */
    VerticalL->addItem(Horizantel);
    VerticalL->addWidget(error);
    VerticalL->addWidget(Login_Button,2,0);
    VerticalL->addWidget(LoginGuest_Button,3,0);
    VerticalL->addWidget(Register_Button,4,0);
    this->setLayout(VerticalL);

    /**
     * Signal connector to go to REGISTER MENU
     */

    QObject::connect(Register_Button, SIGNAL(clicked()), this, SLOT(OpenRegisterMenu()) );

    /**
     * Signal connector to mainscreen
     */
    QObject::connect(Login_Button, SIGNAL(clicked()), this, SLOT(Open_GameSelection()) );




}

/**
 * \brief Function which opens REGISTER MENU
 * \param Takes no parameter
 * \return nothing (type: void)
 */

void MainMenu_Widget :: OpenRegisterMenu()
{
    this->close();
    partner1 = new RegisterMenu();
    partner1->show();
}

/**
 * \brief Function that opens GAME SELECTION MENU
 * \param Takes no parameter
 * \return nothing (type: void)
 */

void MainMenu_Widget :: Open_GameSelection()
{

    bool UsernameUsed = false;
    QFile file("UserData.txt");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QRegExp rx("(\\ |\\,|\\.|\\:|\\t)"); //RegEx for ' ' or ',' or '.' or ':' or '\t'
    QTextStream lite(&file);
    QString sp;
    QStringList query;


    while(!lite.atEnd())
    {

        sp = lite.readLine();
        query = sp.split(rx);

        if(Username->text() == query[4] && Password->text() == query[5])
        {
            UsernameUsed = true;
            break;
        }

    }
    file.close();

    if(UsernameUsed == true)
    {
        partner2 = new MainScreen();
        //partner2->user = Username->text();
        partner2->setUser(Username->text());
        this->close();
        partner2->show();
    }
    else
    {
        error->setText("Wrong Username or Password");
    }

}

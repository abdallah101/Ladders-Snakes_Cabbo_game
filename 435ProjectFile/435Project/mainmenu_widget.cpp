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
#include <QPalette>
#include <QPixmap>
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
     * GUI
     */

    this->setStyleSheet("background-color: 	#550949");
    //this->setStyleSheet("background-image: url(./home/eece435l/Downloads/Colorful-Geometric-Simple-Background-Image.jpg)");
    UsernameL->setStyleSheet("QLabel {font: bold; color: #D4AF37}");
    PasswordL ->setStyleSheet("QLabel {font: bold; color: #D4AF37}");
    Username->setStyleSheet("QLineEdit {background: #E1C56A}");
    Password ->setStyleSheet("QLineEdit {background: #E1C56A}");
    Login_Button->setStyleSheet("QPushButton{font: bold; font-size: 14px;font-family: Arial;color: #550949; background-color: #D4AF37;}");
    Register_Button->setStyleSheet("QPushButton{font: bold; font-size: 14px;font-family: Arial;color: #550949; background-color: #D4AF37;}");
    LoginGuest_Button->setStyleSheet("QPushButton{font: bold; font-size: 14px;font-family: Arial;color: #550949; background-color: #D4AF37;}");
    error->setStyleSheet("QLabel {font: bold; color: #D4AF37}");

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



    /**
     * removes message after 4 seconds
     */
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(4000);


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

void MainMenu_Widget :: update()
{
    error->setText("");
}

void MainMenu_Widget :: keyPressEvent (QKeyEvent * event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
    {
        this->Open_GameSelection();
    }
}


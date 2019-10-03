#include "mainmenu_widget.h"
#include <QApplication>
#include <QWidget>
#include <QtWidgets>
#include <strings.h>
#include <QLabel>
#include <QLayout>
#include <registermenu.h>


MainMenu_Widget::MainMenu_Widget(QWidget *parent) :
    QWidget(parent)
{

    //Creating buttons, input boxes, and Labels
    Login_Button = new QPushButton("Login");
    Register_Button = new QPushButton("Register");
    LoginGuest_Button = new QPushButton("Login as Guest");
    Username = new QLineEdit();
    Password = new QLineEdit();
    UsernameL = new QLabel("Username: ");
    PasswordL = new QLabel("Password: ");


    //Creating layouts
    VerticalL = new QVBoxLayout();
    Horizantel = new QGridLayout();

    //adding widgets to horizantel layout
    Horizantel->addWidget(Username,1,0);
    Horizantel->addWidget(Password,1,2);
    Horizantel->addWidget(UsernameL,0,0);
    Horizantel->addWidget(PasswordL,0,2);

    //adding widgets to vertical layout
    VerticalL->addItem(Horizantel);
    VerticalL->addWidget(Login_Button,1,0);
    VerticalL->addWidget(LoginGuest_Button,2,0);
    VerticalL->addWidget(Register_Button,3,0);
    this->setLayout(VerticalL);

    //Signal connector to go to REGISTER MENU
    QObject::connect(Register_Button, SIGNAL(clicked()), this, SLOT(OpenRegisterMenu()) );




}

//Function to open REGISTER MENU
void MainMenu_Widget :: OpenRegisterMenu()
{
    this->close();
    partner1 = new RegisterMenu();
    partner1->show();

}


//Function to open GAME SELECTION MENU
void MainMenu_Widget :: Open_GameSelection()
{

}

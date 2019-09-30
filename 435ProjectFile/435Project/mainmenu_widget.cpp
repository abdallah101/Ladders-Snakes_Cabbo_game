#include "mainmenu_widget.h"
#include <QApplication>
#include <QWidget>
#include <QtWidgets>
#include <strings.h>
#include <QLabel>
#include <QLayout>

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


    VerticalL = new QVBoxLayout();
    Horizantel = new QGridLayout();
    GroupBox = new QGroupBox();





    //Horizantel->addWidget(LoginGuest_Button,4,1);
    //Horizantel->addWidget(Login_Button,3,1);
    //Horizantel->addWidget(Register_Button,5,1);
    Horizantel->addWidget(Username,1,0);
    Horizantel->addWidget(Password,1,2);
    Horizantel->addWidget(UsernameL,0,0);
    Horizantel->addWidget(PasswordL,0,2);






     //Horizantel->addItem(new QSpacerItem(50,10),0,2,1,1);

    VerticalL->addItem(Horizantel);
    VerticalL->addWidget(Login_Button,1,0);
    VerticalL->addWidget(LoginGuest_Button,2,0);
    VerticalL->addWidget(Register_Button,3,0);





    setLayout(VerticalL);




    this->setLayout(VerticalL);




}

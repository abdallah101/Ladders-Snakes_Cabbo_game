#include "registermenu.h"
#include <QtWidgets>
#include <QApplication>
#include <mainmenu_widget.h>
#include <QWidget>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QDebug>

RegisterMenu::RegisterMenu(QWidget *parent) :
    QWidget(parent)
{
    Register = new QPushButton ("Register");
    InsertImage = new QPushButton ("Insert Profile Image");
    FirstName = new QLabel ("First Name");
    LastName = new QLabel ("Last Name");
    Gender = new QLabel ("Gender");
    Age = new QLabel ("Age");
    MaleLabel = new QLabel ("Male");
    FemaleLabel = new QLabel ("Female");
    LineEdit1 = new QLineEdit();
    LineEdit2 = new QLineEdit();
    Dialog = new QDialogButtonBox();
    Male = new QRadioButton("Male");
    Female = new QRadioButton("Female");

    SpinBox = new QSpinBox();


    VerticalL = new QVBoxLayout();
    Horizantel = new QGridLayout();
    GroupBox = new QGroupBox();
    QV = new QVBoxLayout();
    QV->addWidget(Male);
    QV->addWidget(Female);
    GroupBox->setLayout(QV);




    Horizantel->addWidget(FirstName,0,0);
    Horizantel->addWidget(LastName,1,0);
    Horizantel->addWidget(Gender,2,0);
    Horizantel->addWidget(Age,0,2);
    Horizantel->addWidget(LineEdit1,0,1);
    Horizantel->addWidget(LineEdit2,1,1);
    Horizantel->addWidget(SpinBox,0,3);
    Horizantel->addWidget(InsertImage,3,0);


    Horizantel->addWidget(GroupBox,2,1);


    Horizantel->addItem(new QSpacerItem(50,10),0,2,1,1);

    VerticalL->addItem(Horizantel);


    VerticalL->addWidget(Register,2,0);




    setLayout(VerticalL);




    this->setLayout(VerticalL);
    //window->show();
    QObject::connect(Register, SIGNAL(clicked()), this, SLOT(RegisterUser()) );
    QObject::connect(InsertImage, SIGNAL(clicked()), this, SLOT(GetImg()) );


}
void RegisterMenu :: RegisterUser()
{

    QString gender = "Not Set";
    QFile file("UserData.txt");
    file.open(QIODevice::Append|QIODevice::Text);
    QTextStream stream(&file);

    if (Male->isChecked())
    {
        gender = "Male";
    }
    if(Female->isChecked())
    {
        gender = "female";
    }

    //lineEdit1 is firstname and lineEdit2 is last name
    stream << "First Name: " << LineEdit1->text() << ", Last Name: " << LineEdit2->text() << ", Age: "
           << SpinBox->text() << ", Gender: " << gender << endl;

    stream.flush();
    file.close();


}

void RegisterMenu :: GetImg(){






}


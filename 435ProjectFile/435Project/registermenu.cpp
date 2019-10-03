#include "registermenu.h"
#include <QtWidgets>
#include <QApplication>
#include <mainmenu_widget.h>
#include <QWidget>

RegisterMenu::RegisterMenu(QWidget *parent) :
    QWidget(parent)
{
    Finish = new QPushButton ("Finish");
    Refresh = new QPushButton ("Refresh");
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
    TextEdit = new QTextEdit();
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
    Horizantel->addWidget(Refresh,3,0);


    Horizantel->addWidget(GroupBox,2,1);


    Horizantel->addItem(new QSpacerItem(50,10),0,2,1,1);

    VerticalL->addItem(Horizantel);

    VerticalL->addWidget(TextEdit,2,0);
    VerticalL->addWidget(Finish,3,0);




    setLayout(VerticalL);




    this->setLayout(VerticalL);
    //window->show();
    QObject::connect(Finish, SIGNAL(clicked()), this, SLOT(fillSummary()) );
    QObject::connect(Refresh, SIGNAL(clicked()), this, SLOT(refresh()) );


}
void RegisterMenu :: fillSummary()
{
    QString first = LineEdit1->text();
    QString last = LineEdit2->text();
    QString ageS = SpinBox->text();
    QString gender;
    if(Male->isChecked()==true)
    {
        gender = "Male";
    }
    else if (Female->isChecked() == true)
    {
        gender = "Female";
    }
    else
    {
        gender = "Unknown";
    }

    QString summary = first + "\n" + last + "\n" + ageS + "\n" + gender + "\n";

    TextEdit->setText(summary);
}

void RegisterMenu :: refresh(){

    //TextEdit->setText("");
    TextEdit->clear();
    LineEdit1->clear();
    LineEdit2->clear();

    Male->setAutoExclusive(false);
    Male->setChecked(false);
    Male->setAutoExclusive(true);
    Female->setAutoExclusive(false);
    Female->setChecked(false);
    Female->setAutoExclusive(true);




    SpinBox->clear();


}


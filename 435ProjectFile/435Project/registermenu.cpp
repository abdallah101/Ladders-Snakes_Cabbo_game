#include "registermenu.h"
#include <QtWidgets>
#include <QApplication>
#include <mainmenu_widget.h>
#include <QWidget>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <QFileDialog>
#include <QImage>
#include <QPixmap>

RegisterMenu::RegisterMenu(QWidget *parent) :
    QWidget(parent)
{
    //Setting up the interface for registration
    UploadedPicPath = new QLabel("Upload your Profile Picture");
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
    username = new QLineEdit();
    password = new QLineEdit();
    password->setEchoMode(QLineEdit::Password); //making password show dots instead of letters
    usernameL = new QLabel("Username");
    passwordL = new QLabel("Password");
    SpinBox = new QSpinBox();


    //setting up the layout
    VerticalL = new QVBoxLayout();
    Horizantel = new QGridLayout();
    GroupBox = new QGroupBox();
    QV = new QVBoxLayout();
    QV->addWidget(Male);
    QV->addWidget(Female);
    GroupBox->setLayout(QV);



    //setting up the horizantel layout by adding widgets
    Horizantel->addWidget(FirstName,0,0);
    Horizantel->addWidget(LastName,1,0);
    Horizantel->addWidget(usernameL,2,0);
    Horizantel->addWidget(passwordL,3,0);
    Horizantel->addWidget(username,2,1);
    Horizantel->addWidget(password,3,1);
    Horizantel->addWidget(Gender,5,0);
    Horizantel->addWidget(Age,0,2);
    Horizantel->addWidget(LineEdit1,0,1);
    Horizantel->addWidget(LineEdit2,1,1);
    Horizantel->addWidget(SpinBox,0,3);
    Horizantel->addWidget(InsertImage,5,0);
    Horizantel->addWidget(GroupBox,4,1);
    Horizantel->addItem(new QSpacerItem(50,10),0,2,1,1);
    Horizantel->addWidget(UploadedPicPath, 5, 1);


    //Setting up vertical layout
    VerticalL->addItem(Horizantel);
    VerticalL->addWidget(Register,2,0);
    setLayout(VerticalL);
    this->setLayout(VerticalL);

    //connectors
    QObject::connect(Register, SIGNAL(clicked()), this, SLOT(RegisterUser()) );
    QObject::connect(InsertImage, SIGNAL(clicked()), this, SLOT(GetImg()) );


}

//function to register user into database which is a .txt file called UserData.txt
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
    //format is: firstname,lastname,age,gender,username,password
    stream << LineEdit1->text() << "," << LineEdit2->text() << ","<< SpinBox->text() << "," << gender << "," << username->text() <<
              "," << password->text() << endl;

    stream.flush();
    file.close();


}


//function to save user's image to a file called UserProfilePics which is set up as a resource file
void RegisterMenu :: GetImg(){



    QString copyto; //saving name of image with its extension
    QString Extension; //saving only the extension
    bool founddash = false; //used for finding "/" in path
    bool foundextension = false; //used in finding "." in path

    //saves the path to a .jpg .jpeg or .png image that a user is promted to give
    QString imagePath= QFileDialog::getOpenFileName(this,tr("UserProfilePics"),"", tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" ) );

    //looping to find "/" and "." to save name and extension
    for(int i = imagePath.size()-1, indexdash = 0, indexExt = 0; i != imagePath.size();)
    {
        if(imagePath[i] == '/')
        {
            founddash = true;

        }
        if(founddash == false)
        {
            i--;
        }
        //when founddash is true, i start taking in the letters ie. everything after "/" and including it
        else
        {
            copyto[indexdash] = imagePath[i];
            i++;
            indexdash++;
            if(imagePath[i] == '.')
            {
                foundextension = true;

            }
            //when foundextension is true, i start taking in the letters ie. everything after "." and including it
            if(foundextension == true)
            {
                Extension[indexExt] = imagePath[i];
                indexExt++;
            }
        }

    }



    //showing user his selected item
    UploadedPicPath->setText(imagePath);


    //copying the item the user selected into UserProfilePics which is a resource file
    QFile::copy(imagePath,
                QDir::currentPath() +"/UserProfilePics"+ copyto);

    //copying it again but changing its name so that we identify it uniquely
    QFile::copy(QDir::currentPath() + "/UserProfilePics"+ copyto,
                QDir::currentPath()+ "/UserProfilePics/" + username->text()
                + Extension
                );

    //deleting the original one with bad name
    QFile::remove(QDir::currentPath() +"/UserProfilePics"+ copyto);








}


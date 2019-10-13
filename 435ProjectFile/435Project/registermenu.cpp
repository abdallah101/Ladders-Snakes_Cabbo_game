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
#include <QString>

RegisterMenu::RegisterMenu(QWidget *parent) :
    QWidget(parent)
{
    //Setting up the interface for registration
    errorNotice = new QLabel();
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
    back = new QPushButton("back");

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
    Horizantel->addWidget(GroupBox,4,0);
    Horizantel->addItem(new QSpacerItem(50,10),0,2,1,1);
    Horizantel->addWidget(UploadedPicPath, 5, 1);
    Horizantel->addWidget(errorNotice,4,1 );

    //Setting up RBL
    RBL = new QGridLayout();
    RBL->addWidget(Register, 0 , 0);
    RBL->addWidget(back, 0, 1);


    //Setting up vertical layout
    VerticalL->addItem(Horizantel);
    VerticalL->addItem(RBL);
    setLayout(VerticalL);
    this->setLayout(VerticalL);

    //connectors
    QObject::connect(Register, SIGNAL(clicked()), this, SLOT(RegisterUser()) );
    QObject::connect(InsertImage, SIGNAL(clicked()), this, SLOT(GetImg()) );
    QObject::connect(back, SIGNAL(clicked()), this, SLOT(goBack()) );


}

/**
  * @brief Check the password
  * @param string password
  * @return integer that is 0 if no problem| 1 if password is short| 2 if character is missing.
  */

int RegisterMenu :: CheckPassword(QString Password)
{
    if (Password.length() < 10) return 1;
    int  small = 0, big = 0;
    for (int i = 0; i<Password.length(); i++)
    {
        if (Password[i] >= 'a' && Password[i] <='z') small++;
        else if(Password[i] >= 'A' && Password[i] <='Z') big++;
    }
    if (small == 0 || big == 0 || (small + big == Password.length())) return 2;
    return 0;
}

//function to register user into database which is a .txt file called UserData.txt
void RegisterMenu :: RegisterUser()
{

    QString gender = "n";

    bool UsernameUsed = false;

    if (Male->isChecked())
     {
            gender = "Male";
    }
   if(Female->isChecked())
   {
        gender = "female";
    }


   if(LineEdit1->text().isEmpty()==true || username->text().isEmpty() == true || LineEdit2->text().isEmpty() == true ||
           password->text().isEmpty() == true || gender == "n" || SpinBox->text().isEmpty() == true)
   {
       UsernameUsed = true;
       errorNotice->setText("Please insert all required fields");
   }

   if(SpinBox->text().toDouble() < 10)
   {
       UsernameUsed = true;
       errorNotice->setText("You have to be above 10 to play this game");
   }

   int x = CheckPassword(password->text());
   if (x != 0)
   {
       UsernameUsed = true;
       if (x == 1) errorNotice->setText("The password must be at least 10 characters.");
       else errorNotice->setText("The password must contain at least one small letter, one capital letter, and one non-alphabetical character.");
   }

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

        if(username->text() == query[4])
        {
            errorNotice->setText("Username Used");
            UsernameUsed = true;
            break;
        }

    }
    file.close();


    if(UsernameUsed == false)
    {


      file.open(QIODevice::Append|QIODevice::Text);
      QTextStream stream(&file);




      //lineEdit1 is firstname and lineEdit2 is last name
       //format is: firstname,lastname,age,gender,username,password seperated by commas
        stream << LineEdit1->text() << "," << LineEdit2->text() << ","<< SpinBox->text() << "," << gender << "," << username->text() <<
                  "," << password->text() << endl;

        stream.flush();
        file.close();



    QString copyto; //saving name of image with its extension
    QString Extension; //saving only the extension
    bool founddash = false; //used for finding "/" in path
    bool foundextension = false; //used in finding "." in path

    QString imagePath = UploadedPicPath->text();
    QFile search(imagePath);

    if (search.exists())
    {
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


    this->close();
    partner1 = new MainMenu_Widget();
    partner1->show();
    }
}


//function to save user's image to a file called UserProfilePics which is set up as a resource file
void RegisterMenu :: GetImg(){

    //saves the path to a .jpg .jpeg or .png image that a user is promted to give
    QString imagePath= QFileDialog::getOpenFileName(this,tr("UserProfilePics"),"", tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" ) );


    //showing user his selected item
    UploadedPicPath->setText(imagePath);

}

void RegisterMenu :: goBack()
{
    this->close();
    partner1 = new MainMenu_Widget();
    partner1->show();
}


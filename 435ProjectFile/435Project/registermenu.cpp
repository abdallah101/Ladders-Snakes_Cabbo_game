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
#include <QDate>

/**
  *\file registermenu.cpp
  * Setting up the interface for registration
  */

RegisterMenu::RegisterMenu(QWidget *parent) :
    QWidget(parent)
{
    errorNotice = new QLabel();
    UploadedPicPath = new QLabel("Upload your Profile Picture.");
    Register = new QPushButton ("Register");
    InsertImage = new QPushButton ("Insert Profile Image.");
    FirstName = new QLabel ("First Name");
    LastName = new QLabel ("Last Name");
    Gender = new QLabel ("Gender");
    MaleLabel = new QLabel ("Male");
    FemaleLabel = new QLabel ("Female");
    LineEdit1 = new QLineEdit();
    LineEdit2 = new QLineEdit();
    username = new QLineEdit();
    password = new QLineEdit();
    Dialog = new QDialogButtonBox();
    Male = new QRadioButton("Male");
    Female = new QRadioButton("Female");
    usernameL = new QLabel("Username");
    passwordL = new QLabel("Password");
    back = new QPushButton("back");
    birthdate = new QLabel("Birth Date(D/M/Y):");
    day = new QSpinBox();
    month = new QSpinBox();
    year = new QSpinBox();

    password->setEchoMode(QLineEdit::Password); //making password show dots instead of letters
    day->setRange(1,31);
    month->setRange(1,31);
    year->setRange(1900, QDate::currentDate().year());

    /**
     * setting up the layout
     */

    VerticalL = new QVBoxLayout();
    Horizantel = new QGridLayout();
    GroupBox = new QGroupBox();
    QV = new QVBoxLayout();
    QV->addWidget(Male);
    QV->addWidget(Female);
    GroupBox->setLayout(QV);

    birthlayout = new QGridLayout();
    birthbox = new QGroupBox();
    birthlayout->addWidget(day,0,0);
    birthlayout->addWidget(month,0,1);
    birthlayout->addWidget(year,0,2);
    birthbox->setLayout(birthlayout);



    /**
     * setting up the horizantel layout by adding widgets
     */

    //order here determines tab order as well
    Horizantel->addWidget(FirstName,0,0);
    Horizantel->addWidget(LastName,1,0);
    Horizantel->addWidget(usernameL,2,0);
    Horizantel->addWidget(passwordL,3,0);
    Horizantel->addWidget(Gender,4,0);
    Horizantel->addWidget(LineEdit1,0,1);
    Horizantel->addWidget(LineEdit2,1,1);
    Horizantel->addWidget(username,2,1);
    Horizantel->addWidget(password,3,1);
    Horizantel->addWidget(birthdate,5,0);
    Horizantel->addWidget(birthbox,5,1);
    Horizantel->addWidget(InsertImage,7,0);
    Horizantel->addWidget(GroupBox,4,1);
    Horizantel->addItem(new QSpacerItem(50,10),0,2,1,1);
    Horizantel->addWidget(UploadedPicPath, 7, 1);

    /**
     * Setting up RBL
     */

    RBL = new QGridLayout();
    RBL->addWidget(Register, 0 , 0);
    RBL->addWidget(back, 0, 1);


    /**
     * Setting up vertical layout
     */

    VerticalL->addItem(Horizantel);
    VerticalL->addItem(RBL);
    VerticalL->addWidget(errorNotice);
    setLayout(VerticalL);
    this->setLayout(VerticalL);

    /**
     * connectors
     */
    QObject::connect(Register, SIGNAL(clicked()), this, SLOT(RegisterUser()) );
    QObject::connect(InsertImage, SIGNAL(clicked()), this, SLOT(GetImg()) );
    QObject::connect(back, SIGNAL(clicked()), this, SLOT(goBack()) );

    /**
     * removes message after 3 seconds
     */
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

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

/**
  * @brief function to register user into database which is a .txt file called UserData.txt
  * @param empty
  * @return void
  */

void RegisterMenu :: RegisterUser()
{

    age = this->findAge(QDate::currentDate().day(),QDate::currentDate().month(),QDate::currentDate().year(),
                  day->text().toInt(),month->text().toInt(),year->text().toInt());

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
           password->text().isEmpty() == true || gender == "n")
   {
       UsernameUsed = true;
       errorNotice->setText("Please insert all required fields");
       timer->start(3000);
   }

   if(age < 10)
   {
       UsernameUsed = true;
       errorNotice->setText("You have to be above 10 to play this game");
       timer->start(3000);
   }

   int x = CheckPassword(password->text());
   if (x != 0)
   {
       UsernameUsed = true;
       if (x == 1) errorNotice->setText("The password must be at least 10 characters.");
       else errorNotice->setText("The password must contain at least one small letter, one capital letter, and one non-alphabetical character.");
       timer->start(3000);
   }

    QFile file(QDir::currentPath() + "/UserData.txt");
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

       QFile filehis(QDir::currentPath() + "/history.txt");
       filehis.open(QIODevice::Append|QIODevice::Text);
       QTextStream streamhis(&filehis);

       //the -1 indicates that the user still doesn't have any history (aka fresh account)
       streamhis << username->text() << ",-3,"  <<  endl;
       streamhis.flush();
       filehis.close();

       QFile filehis2(QDir::currentPath() + "/history1.txt");
       filehis2.open(QIODevice::Append|QIODevice::Text);
       QTextStream streamhis2(&filehis2);

       //the -1 indicates that the user still doesn't have any history (aka fresh account)
       streamhis2 << username->text() << ",-3,"  <<  endl;
       streamhis2.flush();
       filehis2.close();


      file.open(QIODevice::Append|QIODevice::Text);
      QTextStream stream(&file);

      /**
       * lineEdit1 is firstname and lineEdit2 is last name
       */

      /**
       *format is: firstname,lastname,age,gender,username,password,day,month,year seperated by commas (csv type)
        */

        stream << LineEdit1->text() << "," << LineEdit2->text() << ","<< age << "," << gender << "," << username->text() <<
                  "," << password->text() << "," << day->text() << "," << month->text() << "," << year->text() << endl;

        stream.flush();
        file.close();


    /**
     * saving name of image with its extension
     */

    QString copyto;

    /**
     * saving only the extension
     */
    QString Extension;

    /**
     * @brief used for finding "/" in path
     */
    bool founddash = false;

    /**
     * @brief used in finding "." in path
     */
    bool foundextension = false;

    QString imagePath = UploadedPicPath->text();
    QFile search(imagePath);

    if (search.exists())
    {
        /**
         * looping to find "/" and "." to save name and extension
         */

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
            /**
             * when founddash is true, i start taking in the letters ie. everything after "/" and including it
             */

            else
            {
                copyto[indexdash] = imagePath[i];
                i++;
                indexdash++;
                if(imagePath[i] == '.')
                {
                    foundextension = true;

                }

                /**
                 * when foundextension is true, i start taking in the letters ie. everything after "." and including it
                 */

                if(foundextension == true)
                {
                    Extension[indexExt] = imagePath[i];
                    indexExt++;
                }
            }

        }

        /**
         * @brief copying the item the user selected into UserProfilePics which is a resource file
         */

        QFile::copy(imagePath,
                    QDir::currentPath() +"/UserProfilePics"+ copyto);

        /**
         * @brief copying it again but changing its name so that we identify it uniquely
        */

        QFile::copy(QDir::currentPath() + "/UserProfilePics"+ copyto,
                    QDir::currentPath()+ "/UserProfilePics/" + username->text()
                    + Extension
                    );

        /**
         * @brief deleting the original one with bad name
         */

        QFile::remove(QDir::currentPath() +"/UserProfilePics"+ copyto);
    }


    this->close();
    partner1 = new MainMenu_Widget();
    partner1->RegSuccess();
    partner1->show();
    }
}

/**
 * \brief Function that saves user's image to a file called UserProfilePics which is set up as a resource file
 * \param Takes no parameter
 * \return nothing (type: void)
 */

void RegisterMenu :: GetImg(){

    /**
     * saves the path to a .jpg .jpeg or .png image that a user is promted to give
     */

    QString imagePath= QFileDialog::getOpenFileName(this,tr("UserProfilePics"),"", tr("JPEG (*.jpg *.jpeg)" ) );


    /**
      * showing user his selected item
      */

    UploadedPicPath->setText(imagePath);

}

/**
 * \brief Function that takes the user back to main menu
 * \param Takes no parameter
 * \return nothing (type: void)
 */

void RegisterMenu :: goBack()
{
    this->close();
    partner1 = new MainMenu_Widget();
    partner1->show();
}


/**
  * @brief Updates the error label to nothing to remove the message displayed
  * @param string password
  * @return nothing (type:void)
  */

void RegisterMenu :: update()
{
    errorNotice->setText("");
}


/**
  * @brief Function that returns the age of a person give his date of birth and the current date
  * @param int current_date, int current_month, int current_year, int birth_date, int_birth_month, int birth_year
  * @return integer that is the age of the person
  */

int RegisterMenu :: findAge(int current_date, int current_month,
             int current_year, int birth_date,
             int birth_month, int birth_year)
{
    /**
     * @brief days of every month
     */

    int month[] = { 31, 28, 31, 30, 31, 30, 31,
                          31, 30, 31, 30, 31 };

    /**
     * @brief  if birth date is greater then current birth month then do not count this month and add 30 to the date so as to subtract the date and get the remaining days
     */

    if (birth_date > current_date) {
        current_date = current_date + month[birth_month - 1];
        current_month = current_month - 1;
    }

    /**
     * @brief if birth month exceeds current month, then do not count this year and add 12 to the month so that we can subtract and find out the difference
     */

    if (birth_month > current_month) {
        current_year = current_year - 1;
        current_month = current_month + 12;
    }

    int calculated_year = current_year - birth_year;

    return calculated_year;
}


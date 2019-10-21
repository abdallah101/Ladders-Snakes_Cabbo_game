#include "settings.h"
#include <QApplication>
#include <QPushButton>
#include <QString>
#include <mainscreen.h>
#include <iostream>

Settings::Settings(QWidget *parent) :
    QWidget(parent)
{



    //declaring
    ChangePassword = new QPushButton("Change Password");
    ChangeProfile = new QPushButton("Change Profile Picture");
    Username = new QLabel("Username:");
    FirstName = new QLabel("First Name:");
    LastName = new QLabel("Last Name:");
    Gender = new QLabel("Gender:");
    back = new QPushButton("Back");
    oldPassword = new QLineEdit();
    oldP = new QLabel("Old Password: ");
    newP = new QLabel("New Password: ");
    error = new QLabel("");
    newPassword = new QLineEdit();
    age = new QLabel("Age: ");

    //setting layout
    Vbox = new QVBoxLayout();
    HorizantelLayout = new QGridLayout();
    HorizantelLayout->addWidget(age, 2,0);
    HorizantelLayout->addWidget(FirstName,0,0);
    HorizantelLayout->addWidget(LastName,0,2);
    HorizantelLayout->addWidget(Username,1,0);
    HorizantelLayout->addWidget(Gender,1,2);
    HorizantelLayout->addWidget(oldP, 3,0);
    HorizantelLayout->addWidget(oldPassword,3,2);
    HorizantelLayout->addWidget(newP, 4, 0);
    HorizantelLayout->addWidget(newPassword,4,2);
    Vbox->addItem(HorizantelLayout);
    Vbox->addWidget(ChangePassword);
    Vbox->addWidget(ChangeProfile);
    Vbox->addWidget(back);
    Vbox->addWidget(error);
    this->setLayout(Vbox);


    QObject::connect(back, SIGNAL(clicked()), this, SLOT(goBack()) );
    QObject::connect(ChangePassword, SIGNAL(clicked()), this, SLOT(ChangePass()) );
    QObject::connect(ChangeProfile, SIGNAL(clicked()), this, SLOT(ChangePic()) );


    /**
     * removes message after 3 seconds
     */
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(3000);





}

void Settings :: update()
{
    error->setText("");
}

void Settings :: ChangePass ()
{
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

        if(user == query[4]) break;

    }
    file.close();

    if(query[5] != oldPassword->text())
    {
        error->setText("Wrong old password");
    }
    else
    {
        int x = CheckPassword(newPassword->text());
        if (x != 0)
        {

            if (x == 1) error->setText("The password must be at least 10 characters.");
            else error->setText("The password must contain at least one small letter, one capital letter, and one non-alphabetical character.");
        }
        else
        {
                QFile data(QDir::currentPath() + "/UserData.txt");
                data.open(QIODevice::Text | QIODevice::ReadOnly);
                QString dataText = data.readAll();

                QRegularExpression re(query[0] + "," + query[1] + "," + query[2] + "," + query[3] + "," + query[4] + "," + query[5]);

                dataText.replace(re, query[0] + "," + query[1] + "," + query[2] + "," + query[3] + "," + query[4] + "," + newPassword->text());
                data.close();
                QFile newData(QDir::currentPath() + "/UserData.txt");
                data.resize(0);
                if(newData.open(QFile::WriteOnly | QFile::Truncate))
                {
                    QTextStream out(&newData);
                    out << dataText;
                }
                newData.close();

                error->setText("Password Changed");



        }

    }

}

void Settings :: ChangePic ()
{
    /**
     * saves the path to a .jpg .jpeg or .png image that a user is promted to give
     */

    QString imagePath= QFileDialog::getOpenFileName(this,tr("UserProfilePics"),"", tr("JPEG (*.jpg *.jpeg)" ) );


    /**
      * showing user his selected item
      */



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
         * @brief removing old profile picture (checking if its .jpg or .jpeg)
         */

        if(QFile::exists(QDir::currentPath() +"/UserProfilePics/" + user + ".jpg"))
        {
            QFile::remove(QDir::currentPath() +"/UserProfilePics/" + user + ".jpg");
        }
        else if (QFile::exists(QDir::currentPath() +"/UserProfilePics/" + user + ".jpeg"))
        {
            QFile::remove(QDir::currentPath() +"/UserProfilePics/" + user + ".jpeg");
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
                    QDir::currentPath()+ "/UserProfilePics/" + user
                    + Extension
                    );

        /**
         * @brief deleting the original one with bad name
         */

        QFile::remove(QDir::currentPath() +"/UserProfilePics"+ copyto);
        error->setText("successfully changed your profile pic to " + imagePath);

}
}

void Settings :: SearchUser (QString d)
{
    this->user = d;

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

        if(this->user == query[4]) break;

    }
    file.close();


    FirstName->setText("First Name: " + query[0]);
    LastName->setText("Last Name: " + query[1]);
    Username->setText("Username: " + query[4]);
    Gender->setText("Gender: " + query[3]);
    age->setText("Age: " + query[2]);
}

void Settings :: goBack()
{
    partner = new MainScreen();
    partner->setUser(user);
    this->close();
    partner->show();
}

int Settings :: CheckPassword(QString Password)
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

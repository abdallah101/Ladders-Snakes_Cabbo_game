#ifndef REGISTERMENU_H
#define REGISTERMENU_H

#include <QWidget>
#include <QObject>
#include <QtWidgets>
#include <strings.h>
#include <QPushButton>
#include <mainmenu_widget.h>
#include <QTimer>


/**
  *\file registermenu.h
  */


class RegisterMenu : public QWidget
{
    Q_OBJECT
public:
    explicit RegisterMenu(QWidget *parent = 0);
    QPushButton * Register, * InsertImage, * back;
    QLabel * FirstName, * LastName, * Gender, * Age, * MaleLabel, * FemaleLabel, * usernameL, * passwordL, *UploadedPicPath, *errorNotice, *birthdate;
    QLineEdit * LineEdit1, * LineEdit2, * username, * password;
    QDialogButtonBox * Dialog;
    QRadioButton * Male, * Female;
    QSpinBox *day, *month, *year;
    QVBoxLayout * VerticalL;
    QGridLayout * Horizantel , *RBL, * birthlayout; //RBL is for register and back buttons
    QGroupBox * GroupBox;
    QGroupBox * birthbox;
    QVBoxLayout *QV;
    QWidget *partner1;
    QTimer * timer;
    int age;

signals:

public slots:
    void RegisterUser();
    void GetImg();
    void goBack();
    int CheckPassword(QString);
    void update();
    int findAge(int current_date, int current_month,
                int current_year, int birth_date,
                int birth_month, int birth_year);
};

#endif // REGISTERMENU_H

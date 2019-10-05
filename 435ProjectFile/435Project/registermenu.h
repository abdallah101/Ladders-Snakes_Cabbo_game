#ifndef REGISTERMENU_H
#define REGISTERMENU_H

#include <QWidget>
#include <QObject>
#include <QtWidgets>
#include <strings.h>
#include <QPushButton>
#include <mainmenu_widget.h>

class RegisterMenu : public QWidget
{
    Q_OBJECT
public:
    explicit RegisterMenu(QWidget *parent = 0);
    QPushButton * Register, * InsertImage, * back;
    QLabel * FirstName, * LastName, * Gender, * Age, * MaleLabel, * FemaleLabel, * usernameL, * passwordL, *UploadedPicPath, *errorNotice;
    QLineEdit * LineEdit1, * LineEdit2, * username, * password;
    QDialogButtonBox * Dialog;
    QRadioButton * Male, * Female;
    QSpinBox * SpinBox;
    QVBoxLayout * VerticalL;
    QGridLayout * Horizantel , *RBL; //RBL is for register and back buttons
    QGroupBox * GroupBox;
    QVBoxLayout *QV;
    QWidget *partner1;

signals:

public slots:
    void RegisterUser();
    void GetImg();
    void goBack();
};

#endif // REGISTERMENU_H

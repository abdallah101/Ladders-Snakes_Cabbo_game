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
    QPushButton * Register, * InsertImage;
    QLabel * FirstName, * LastName, * Gender, * Age, * MaleLabel, * FemaleLabel;
    QLineEdit * LineEdit1, * LineEdit2;
    QDialogButtonBox * Dialog;
    QRadioButton * Male, * Female;

    QSpinBox * SpinBox;
    QVBoxLayout * VerticalL;
    QGridLayout * Horizantel;
    QGroupBox * GroupBox;
    QVBoxLayout *QV;

signals:

public slots:
    void RegisterUser();
    void GetImg();

};

#endif // REGISTERMENU_H

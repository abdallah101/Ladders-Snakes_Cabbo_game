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
    QPushButton * Finish, * Refresh;
    QLabel * FirstName, * LastName, * Gender, * Age, * MaleLabel, * FemaleLabel;
    QLineEdit * LineEdit1, * LineEdit2;
    QDialogButtonBox * Dialog;
    QRadioButton * Male, * Female;
    QTextEdit * TextEdit;
    QSpinBox * SpinBox;
    QVBoxLayout * VerticalL;
    QGridLayout * Horizantel;
    QGroupBox * GroupBox;
    QVBoxLayout *QV;

signals:

public slots:
    void fillSummary();
    void refresh();

};

#endif // REGISTERMENU_H

/********************************************************************************
** Form generated from reading UI file 'dices.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DICES_H
#define UI_DICES_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dices
{
public:

    void setupUi(QWidget *Dices)
    {
        if (Dices->objectName().isEmpty())
            Dices->setObjectName(QStringLiteral("Dices"));
        Dices->resize(400, 300);

        retranslateUi(Dices);

        QMetaObject::connectSlotsByName(Dices);
    } // setupUi

    void retranslateUi(QWidget *Dices)
    {
        Dices->setWindowTitle(QApplication::translate("Dices", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class Dices: public Ui_Dices {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DICES_H

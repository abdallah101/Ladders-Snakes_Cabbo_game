#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QtWidgets>
#include <QString>
#include <QTimer>

class MainScreen; //forward declaration

class Settings : public QWidget
{
    Q_OBJECT
public:
    explicit Settings(QWidget *parent = 0);

    QPushButton * ChangePassword, * ChangeProfile, * back;
    QLabel * Username, * FirstName, *LastName, * Gender, *oldP , * newP, *error, * age;
    QVBoxLayout * Vbox;
    QGridLayout * HorizantelLayout;
    QLineEdit * oldPassword, * newPassword;
    QString user;
    MainScreen * partner;
    QTimer * timer;



signals:




public slots:

    void SearchUser(QString h);
    void goBack();
    void ChangePass();
    int CheckPassword(QString h);
    void ChangePic();
    void update();


};

#endif // SETTINGS_H

#ifndef WINLOSE_H
#define WINLOSE_H

#include <QWidget>
#include <QApplication>
#include <QtWidgets>
#include <QString>
#include <mainscreen.h>

class winlose : public QWidget
{
    Q_OBJECT
public:
    explicit winlose(QWidget *parent = 0);
    QLabel * win;
    QPushButton * done;
    QVBoxLayout * vert;
    QString user;
    MainScreen * BackToMain;

signals:

public slots:

    void exit();
    void setlabel(QString a, int b);

};

#endif // WINLOSE_H

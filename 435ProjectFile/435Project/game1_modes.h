#ifndef GAME1_MODES_H
#define GAME1_MODES_H
#include <QWidget>
#include <QObject>
#include <QPushButton>
#include <QGridLayout>

class Game1_Modes : public QWidget
{
    Q_OBJECT
public:
    explicit Game1_Modes(QWidget *parent = 0);
    QPushButton * ComputerEasy, * ComputerHard, * Players2;
    QGridLayout * HMode;
    QWidget * nxtscene;

public slots:
    void start1();
    void start2();
    void start3();
};

#endif // GAME1_MODES_H

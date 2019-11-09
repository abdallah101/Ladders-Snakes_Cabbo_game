#ifndef CUSTWID_H
#define CUSTWID_H
#include <QWidget>
#include <QObject>
#include <QtWidgets>
#include <strings.h>
#include <QPushButton>
#include <dice.h>
#include <QTimer>




class custWid: public QWidget
{
    Q_OBJECT
public:
    explicit custWid(QWidget *parent = 0);
    QPushButton * Submit, *Done, *ReadFromText;
    QSpinBox * from, * to;
    QRadioButton * Ladder, * Snake;
    QLabel * fromL, * toL, * error;
    QVBoxLayout * custVertical;
    QGridLayout * custHorizontal1, * custHorizontal2, * custHorizontal3, * custHorizontal4;
    dice * sceneCust;
    QDialogButtonBox *InsertText;
    QString user, name;
    int difficulty, starterplayer;
    //custWid * customboard;
    QTimer * timer;

public slots:
    void SubmitFunction();
    void SubmitF();
    void DoneFunction();
    //void GetText();
    void FillGrid();
    void update();
    void SetUser (QString d, QString a, int diff, int s);
};

#endif // CUSTWID_H

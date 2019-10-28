#ifndef CUSTWID_H
#define CUSTWID_H
#include <QWidget>
#include <QObject>
#include <QtWidgets>
#include <strings.h>
#include <QPushButton>
#include <game1_scenecust.h>
#include <dicecust.h>


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
    diceCust * sceneCust;
    QDialogButtonBox *InsertText;

public slots:
    void SubmitFunction();
    void DoneFunction();
    //void GetText();
    void FillGrid();
    void update();
};

#endif // CUSTWID_H

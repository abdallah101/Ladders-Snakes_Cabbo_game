/****************************************************************************
** Meta object code from reading C++ file 'gameone.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../435Project/gameone.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gameone.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GameOne_t {
    QByteArrayData data[10];
    char stringdata[61];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_GameOne_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_GameOne_t qt_meta_stringdata_GameOne = {
    {
QT_MOC_LITERAL(0, 0, 7),
QT_MOC_LITERAL(1, 8, 5),
QT_MOC_LITERAL(2, 14, 0),
QT_MOC_LITERAL(3, 15, 9),
QT_MOC_LITERAL(4, 25, 7),
QT_MOC_LITERAL(5, 33, 1),
QT_MOC_LITERAL(6, 35, 1),
QT_MOC_LITERAL(7, 37, 6),
QT_MOC_LITERAL(8, 44, 10),
QT_MOC_LITERAL(9, 55, 4)
    },
    "GameOne\0start\0\0customize\0SetUser\0d\0n\0"
    "update\0resumegame\0back\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GameOne[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x0a,
       3,    0,   45,    2, 0x0a,
       4,    2,   46,    2, 0x0a,
       7,    0,   51,    2, 0x0a,
       8,    0,   52,    2, 0x0a,
       9,    0,   53,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GameOne::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GameOne *_t = static_cast<GameOne *>(_o);
        switch (_id) {
        case 0: _t->start(); break;
        case 1: _t->customize(); break;
        case 2: _t->SetUser((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->update(); break;
        case 4: _t->resumegame(); break;
        case 5: _t->back(); break;
        default: ;
        }
    }
}

const QMetaObject GameOne::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_GameOne.data,
      qt_meta_data_GameOne,  qt_static_metacall, 0, 0}
};


const QMetaObject *GameOne::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GameOne::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GameOne.stringdata))
        return static_cast<void*>(const_cast< GameOne*>(this));
    return QWidget::qt_metacast(_clname);
}

int GameOne::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'dice.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../435Project/dice.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dice.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_dice_t {
    QByteArrayData data[17];
    char stringdata[104];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_dice_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_dice_t qt_meta_stringdata_dice = {
    {
QT_MOC_LITERAL(0, 0, 4),
QT_MOC_LITERAL(1, 5, 9),
QT_MOC_LITERAL(2, 15, 0),
QT_MOC_LITERAL(3, 16, 11),
QT_MOC_LITERAL(4, 28, 7),
QT_MOC_LITERAL(5, 36, 7),
QT_MOC_LITERAL(6, 44, 7),
QT_MOC_LITERAL(7, 52, 1),
QT_MOC_LITERAL(8, 54, 1),
QT_MOC_LITERAL(9, 56, 1),
QT_MOC_LITERAL(10, 58, 1),
QT_MOC_LITERAL(11, 60, 1),
QT_MOC_LITERAL(12, 62, 6),
QT_MOC_LITERAL(13, 69, 6),
QT_MOC_LITERAL(14, 76, 9),
QT_MOC_LITERAL(15, 86, 8),
QT_MOC_LITERAL(16, 95, 7)
    },
    "dice\0ThrowBlue\0\0ThrowBluePC\0EndTurn\0"
    "EndGame\0SetUser\0d\0n\0s\0w\0h\0custom\0"
    "reveal\0EndTurnPC\0listener\0wonturn\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_dice[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x0a,
       3,    0,   60,    2, 0x0a,
       4,    0,   61,    2, 0x0a,
       5,    0,   62,    2, 0x0a,
       6,    6,   63,    2, 0x0a,
      13,    0,   76,    2, 0x0a,
      14,    0,   77,    2, 0x0a,
      15,    0,   78,    2, 0x0a,
      16,    0,   79,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Bool, QMetaType::Bool,    7,    8,    9,   10,   11,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void dice::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        dice *_t = static_cast<dice *>(_o);
        switch (_id) {
        case 0: _t->ThrowBlue(); break;
        case 1: _t->ThrowBluePC(); break;
        case 2: _t->EndTurn(); break;
        case 3: _t->EndGame(); break;
        case 4: _t->SetUser((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5])),(*reinterpret_cast< bool(*)>(_a[6]))); break;
        case 5: _t->reveal(); break;
        case 6: _t->EndTurnPC(); break;
        case 7: _t->listener(); break;
        case 8: _t->wonturn(); break;
        default: ;
        }
    }
}

const QMetaObject dice::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_dice.data,
      qt_meta_data_dice,  qt_static_metacall, 0, 0}
};


const QMetaObject *dice::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *dice::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dice.stringdata))
        return static_cast<void*>(const_cast< dice*>(this));
    return QWidget::qt_metacast(_clname);
}

int dice::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

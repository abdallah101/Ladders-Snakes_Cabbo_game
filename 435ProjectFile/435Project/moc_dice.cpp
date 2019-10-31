/****************************************************************************
** Meta object code from reading C++ file 'dice.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dice.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dice.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_dice_t {
    QByteArrayData data[9];
    char stringdata0[51];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_dice_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_dice_t qt_meta_stringdata_dice = {
    {
QT_MOC_LITERAL(0, 0, 4), // "dice"
QT_MOC_LITERAL(1, 5, 9), // "ThrowBlue"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 7), // "EndTurn"
QT_MOC_LITERAL(4, 24, 7), // "EndGame"
QT_MOC_LITERAL(5, 32, 7), // "SetUser"
QT_MOC_LITERAL(6, 40, 1), // "d"
QT_MOC_LITERAL(7, 42, 1), // "n"
QT_MOC_LITERAL(8, 44, 6) // "reveal"

    },
    "dice\0ThrowBlue\0\0EndTurn\0EndGame\0SetUser\0"
    "d\0n\0reveal"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_dice[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    0,   40,    2, 0x0a /* Public */,
       4,    0,   41,    2, 0x0a /* Public */,
       5,    2,   42,    2, 0x0a /* Public */,
       8,    0,   47,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    6,    7,
    QMetaType::Void,

       0        // eod
};

void dice::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        dice *_t = static_cast<dice *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ThrowBlue(); break;
        case 1: _t->EndTurn(); break;
        case 2: _t->EndGame(); break;
        case 3: _t->SetUser((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->reveal(); break;
        default: ;
        }
    }
}

const QMetaObject dice::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_dice.data,
      qt_meta_data_dice,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *dice::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *dice::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_dice.stringdata0))
        return static_cast<void*>(const_cast< dice*>(this));
    return QWidget::qt_metacast(_clname);
}

int dice::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

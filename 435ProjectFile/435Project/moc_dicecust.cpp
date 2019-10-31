/****************************************************************************
** Meta object code from reading C++ file 'dicecust.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dicecust.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dicecust.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_diceCust_t {
    QByteArrayData data[8];
    char stringdata0[71];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_diceCust_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_diceCust_t qt_meta_stringdata_diceCust = {
    {
QT_MOC_LITERAL(0, 0, 8), // "diceCust"
QT_MOC_LITERAL(1, 9, 13), // "ThrowBlueCust"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 12), // "ThrowRedCust"
QT_MOC_LITERAL(4, 37, 11), // "EndTurnCust"
QT_MOC_LITERAL(5, 49, 11), // "EndGameCust"
QT_MOC_LITERAL(6, 61, 7), // "SetUser"
QT_MOC_LITERAL(7, 69, 1) // "d"

    },
    "diceCust\0ThrowBlueCust\0\0ThrowRedCust\0"
    "EndTurnCust\0EndGameCust\0SetUser\0d"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_diceCust[] = {

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
       5,    0,   42,    2, 0x0a /* Public */,
       6,    1,   43,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,

       0        // eod
};

void diceCust::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        diceCust *_t = static_cast<diceCust *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ThrowBlueCust(); break;
        case 1: _t->ThrowRedCust(); break;
        case 2: _t->EndTurnCust(); break;
        case 3: _t->EndGameCust(); break;
        case 4: _t->SetUser((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject diceCust::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_diceCust.data,
      qt_meta_data_diceCust,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *diceCust::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *diceCust::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_diceCust.stringdata0))
        return static_cast<void*>(const_cast< diceCust*>(this));
    return QWidget::qt_metacast(_clname);
}

int diceCust::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

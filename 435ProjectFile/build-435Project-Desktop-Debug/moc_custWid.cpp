/****************************************************************************
** Meta object code from reading C++ file 'custWid.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../435Project/custWid.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'custWid.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_custWid_t {
    QByteArrayData data[12];
    char stringdata[81];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_custWid_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_custWid_t qt_meta_stringdata_custWid = {
    {
QT_MOC_LITERAL(0, 0, 7),
QT_MOC_LITERAL(1, 8, 14),
QT_MOC_LITERAL(2, 23, 0),
QT_MOC_LITERAL(3, 24, 7),
QT_MOC_LITERAL(4, 32, 12),
QT_MOC_LITERAL(5, 45, 8),
QT_MOC_LITERAL(6, 54, 6),
QT_MOC_LITERAL(7, 61, 7),
QT_MOC_LITERAL(8, 69, 1),
QT_MOC_LITERAL(9, 71, 1),
QT_MOC_LITERAL(10, 73, 4),
QT_MOC_LITERAL(11, 78, 1)
    },
    "custWid\0SubmitFunction\0\0SubmitF\0"
    "DoneFunction\0FillGrid\0update\0SetUser\0"
    "d\0a\0diff\0s\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_custWid[] = {

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
       4,    0,   46,    2, 0x0a,
       5,    0,   47,    2, 0x0a,
       6,    0,   48,    2, 0x0a,
       7,    4,   49,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Int, QMetaType::Int,    8,    9,   10,   11,

       0        // eod
};

void custWid::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        custWid *_t = static_cast<custWid *>(_o);
        switch (_id) {
        case 0: _t->SubmitFunction(); break;
        case 1: _t->SubmitF(); break;
        case 2: _t->DoneFunction(); break;
        case 3: _t->FillGrid(); break;
        case 4: _t->update(); break;
        case 5: _t->SetUser((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        default: ;
        }
    }
}

const QMetaObject custWid::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_custWid.data,
      qt_meta_data_custWid,  qt_static_metacall, 0, 0}
};


const QMetaObject *custWid::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *custWid::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_custWid.stringdata))
        return static_cast<void*>(const_cast< custWid*>(this));
    return QWidget::qt_metacast(_clname);
}

int custWid::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

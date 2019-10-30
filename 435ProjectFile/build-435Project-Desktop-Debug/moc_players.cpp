/****************************************************************************
** Meta object code from reading C++ file 'players.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../435Project/players.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'players.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_players_t {
    QByteArrayData data[20];
    char stringdata[184];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_players_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_players_t qt_meta_stringdata_players = {
    {
QT_MOC_LITERAL(0, 0, 7),
QT_MOC_LITERAL(1, 8, 6),
QT_MOC_LITERAL(2, 15, 0),
QT_MOC_LITERAL(3, 16, 8),
QT_MOC_LITERAL(4, 25, 9),
QT_MOC_LITERAL(5, 35, 8),
QT_MOC_LITERAL(6, 44, 13),
QT_MOC_LITERAL(7, 58, 12),
QT_MOC_LITERAL(8, 71, 5),
QT_MOC_LITERAL(9, 77, 8),
QT_MOC_LITERAL(10, 86, 10),
QT_MOC_LITERAL(11, 97, 9),
QT_MOC_LITERAL(12, 107, 10),
QT_MOC_LITERAL(13, 118, 6),
QT_MOC_LITERAL(14, 125, 10),
QT_MOC_LITERAL(15, 136, 6),
QT_MOC_LITERAL(16, 143, 11),
QT_MOC_LITERAL(17, 155, 11),
QT_MOC_LITERAL(18, 167, 7),
QT_MOC_LITERAL(19, 175, 7)
    },
    "players\0MoveUp\0\0activate\0MoveRight\0"
    "MoveLeft\0activateRight\0activateLeft\0"
    "MoveP\0FindCell\0MovePExtra\0MovePCust\0"
    "activateRU\0MoveRU\0activateLU\0MoveLU\0"
    "activateLUR\0activateRUL\0MoveLUR\0MoveRUL\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_players[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  104,    2, 0x0a,
       3,    0,  105,    2, 0x0a,
       4,    0,  106,    2, 0x0a,
       5,    0,  107,    2, 0x0a,
       6,    0,  108,    2, 0x0a,
       7,    0,  109,    2, 0x0a,
       8,    1,  110,    2, 0x0a,
       9,    0,  113,    2, 0x0a,
      10,    1,  114,    2, 0x0a,
      11,    1,  117,    2, 0x0a,
      12,    0,  120,    2, 0x0a,
      13,    0,  121,    2, 0x0a,
      14,    0,  122,    2, 0x0a,
      15,    0,  123,    2, 0x0a,
      16,    0,  124,    2, 0x0a,
      17,    0,  125,    2, 0x0a,
      18,    0,  126,    2, 0x0a,
      19,    0,  127,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void players::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        players *_t = static_cast<players *>(_o);
        switch (_id) {
        case 0: _t->MoveUp(); break;
        case 1: _t->activate(); break;
        case 2: _t->MoveRight(); break;
        case 3: _t->MoveLeft(); break;
        case 4: _t->activateRight(); break;
        case 5: _t->activateLeft(); break;
        case 6: _t->MoveP((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: { int _r = _t->FindCell();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 8: _t->MovePExtra((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->MovePCust((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->activateRU(); break;
        case 11: _t->MoveRU(); break;
        case 12: _t->activateLU(); break;
        case 13: _t->MoveLU(); break;
        case 14: _t->activateLUR(); break;
        case 15: _t->activateRUL(); break;
        case 16: _t->MoveLUR(); break;
        case 17: _t->MoveRUL(); break;
        default: ;
        }
    }
}

const QMetaObject players::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_players.data,
      qt_meta_data_players,  qt_static_metacall, 0, 0}
};


const QMetaObject *players::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *players::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_players.stringdata))
        return static_cast<void*>(const_cast< players*>(this));
    if (!strcmp(_clname, "QGraphicsPixmapItem"))
        return static_cast< QGraphicsPixmapItem*>(const_cast< players*>(this));
    return QObject::qt_metacast(_clname);
}

int players::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
